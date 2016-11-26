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
				stash includes: 'source/**', excludes: '.git', name: 'source'
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
			agent label: 'debian'
			steps {
				unstash 'source'
				sh 'cd enki && debuild -i -us -uc -b'
			}
			post {
				always {
					sh 'pwd'
					sh 'mv libenki*.{deb,changes,build} dist/'
				}
			}
		}
	}
	// post {
	// 	always {
	// 		archiveArtifacts artifacts: 'dist/**', fingerprint: true, onlyIfSuccessful: true
	// 	}
	// }
}
