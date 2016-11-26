#!groovy

pipeline {
	agent label:""
	stages {
		stage("Prepare") {
			steps {
				sh "mkdir -p build dist"
			}
		}
		stage("Checkout") {
			steps {
				dir('enki') {
					checkout scm
				}
				stash excludes: '.git', name: 'source'
			}
		}
		stage("Compile") {
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
				input "Proceed to packaging?"
			}
		}
		stage("Package") {
			steps {
				unstash 'source'
				sh "cd enki && debuild -i -us -uc -b"
			}
			post {
				always {
					sh "mv enki*.deb dist/"
				}
			}
		}
	}
	post {
		always {
			archiveArtifacts artifacts: 'dist/**', fingerprint: true, onlyIfSuccessful: true
		}
	}
}
