#!groovy

// Jenkinsfile for compiling, testing, and packaging the Enki libraries.
// Requires CMake plugin from https://github.com/davidjsherman/aseba-jenkins.git in global library.

pipeline {
	agent any // use any available Jenkins agent
	stages {
		stage('Prepare') {
			steps {
				// checkout scm -- done automatically
				stash includes: 'enki/**', excludes: '.git', name: 'source'
			}
		}
		stage('Compile') {
			parallel {
				stage("Compile on debian") {
					agent {
						label 'debian'
					}
					steps {
						unstash 'source'
						script {
							env.debian_python = sh ( script: '''
									python -c "import sys; print 'lib/python'+str(sys.version_info[0])+'.'+str(sys.version_info[1])+'/dist-packages'"
''', returnStdout: true).trim()
						}
						CMake([label: 'debian',
							   getCmakeArgs: "-DPYTHON_CUSTOM_TARGET:PATH=${env.debian_python}"])
						stash includes: 'dist/**', name: 'dist-debian'
						stash includes: 'build/**', name: 'build-debian'
					}
				}
				stage("Compile on macos") {
					agent {
						label 'macos'
					}
					steps {
						unstash 'source'
						CMake([label: 'macos'])
						stash includes: 'dist/**', name: 'dist-macos'
					}
				}
				stage("Compile on windows") {
					agent {
						label 'windows'
					}
					steps {
						unstash 'source'
						CMake([label: 'windows'])
						stash includes: 'dist/**', name: 'dist-windows'
					}
				}
			}
		}
		stage('Test') {
			parallel {
				stage("Test on debian") {
					agent {
						label 'debian'
					}
					steps {
						unstash 'build-debian'
						dir('build/debian') {
							sh 'LANG=C ctest'
						}
					}
				}
			}
		}
		stage('Package') {
			// Packages are only built for the master branch
			when {
				expression {
					return env.BRANCH == 'master'
				}
			}
			parallel {
				stage("Build debian package") {
					agent {
						label 'debian'
					}
					steps {
						unstash 'dist-debian'
						unstash 'source'
						dir('enki') {
							sh 'which debuild && debuild -i -us -uc -b'
						}
						sh 'mv libenki*.deb libenki*.changes libenki*.build dist/debian/'
						stash includes: 'dist/**', name: 'dist-debian'
					}
				}
			}
		}
		stage('Archive') {
			steps {
				unstash 'dist-debian'
				unstash 'dist-macos'
				unstash 'dist-windows'
				archiveArtifacts artifacts: 'dist/**', fingerprint: true, onlyIfSuccessful: true
			}
		}
	}
}
