#!groovy

// Jenkinsfile for compiling, testing, and packaging the Enki libraries.
// Requires CMake plugin from https://github.com/davidjsherman/aseba-jenkins.git in global library.

pipeline {
	agent label:'' // use any available Jenkins agent
	stages {
		stage('Prepare') {
			steps {
				sh 'mkdir -p build dist'
				dir('enki') {
					checkout scm
				}
				stash includes: 'enki/**', excludes: '.git', name: 'source'
			}
		}
		stage('Compile') {
			steps {
				unstash 'source'
				CMake([buildType: 'Debug',
					   sourceDir: '$workDir/enki',
					   buildDir: '$workDir/build/enki',
					   installDir: '$workDir/dist',
					   getCmakeArgs: [ '-DBUILD_SHARED_LIBS:BOOL=ON' ]
					  ])
			}
			post {
				always {
					stash includes: 'dist/**', name: 'enki'
				}
			}
		}
		stage('Test') {
			steps {
				dir('build/enki') {
					sh 'ctest'
				}
			}
		}
		stage('Package') {
			when {
				sh(script:'which debuild', returnStatus: true) == 0
			}
			steps {
				unstash 'source'
				sh 'cd enki && debuild -i -us -uc -b'
				sh 'mv libenki*.deb libenki*.changes libenki*.build dist/'
			}
		}
		stage('Archive') {
			steps {
				archiveArtifacts artifacts: 'dist/**', fingerprint: true, onlyIfSuccessful: true
			}
		}
	}
}
