#!groovy

pipeline {
	agent label:""
	stages {
		stage("prepare") {
			steps {
				sh "mkdir -p _install _build"
			}
		}
		stage("checkout") {
			steps {
				dir('enki') {
					git branch: 'master', url: 'https://github.com/davidjsherman/enki.git'
				}
				stash excludes: '.git', name: 'source'
			}
		}
		stage("compile") {
			steps {
				unstash 'source'
				CMake([buildType: 'Debug',
					   sourceDir: '$workDir/enki',
					   buildDir: '$workDir/_build/enki',
					   installDir: '$workDir/_install',
					   getCmakeArgs: [ '-DBUILD_SHARED_LIBS:BOOL=ON' ]
					  ])
			}
			post {
				always {
					stash includes: '_install/**', name: 'enki'
				}
			}
		}
	}
	post {
		always {
			archiveArtifacts artifacts: '_install/**', fingerprint: true, onlyIfSuccessful: true
		}
	}
}
