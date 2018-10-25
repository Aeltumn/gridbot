pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh '''

gradle build'''
      }
    }
    stage('Collect Aritfacts') {
      steps {
        archiveArtifacts 'Gridbot'
      }
    }
  }
}