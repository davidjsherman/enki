#!groovy

// Jenkinsfile for compiling, testing, and packaging the Enki libraries.
// Requires CMake plugin from https://github.com/davidjsherman/aseba-jenkins.git global library

pipeline {
	agent none
	stages {
		stage('Prepare') {
			agent label: ''
			steps {
				sh 'mkdir -p build dist'
				dir('enki') {
					checkout scm
				}
				stash includes: 'enki/**', excludes: '.git', name: 'source'
			}
		}
		stage('Compile') {
			agent label: ''
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
		stage('Package') {
			steps {
				parallel (
					"debian": {
						node('missing') {
							unstash 'source'
							sh 'cd enki && debuild -i -us -uc -b'
							sh 'mv libenki*.deb libenki*.changes libenki*.build dist/'
							archiveArtifacts artifacts: 'dist/**', fingerprint: true, onlyIfSuccessful: true
						}
					}
				)
			}
		}
	}
}
