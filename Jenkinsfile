pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh '''

chmod +x ./gradlew
./gradlew build --no-daemon'''
      }
    }
    stage('Collect Aritfacts') {
      steps {
        archiveArtifacts 'Gridbot'
      }
    }
  }
}