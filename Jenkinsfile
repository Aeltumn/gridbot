pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        build 'gradlew build'
      }
    }
    stage('Collect Aritfacts') {
      steps {
        archiveArtifacts 'Gridbot'
      }
    }
  }
}