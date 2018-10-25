pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh '''sudo ./gradlew build'''
      }
    }
    stage('Collect Aritfacts') {
      steps {
        archiveArtifacts 'Gridbot'
      }
    }
  }
}