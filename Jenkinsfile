pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh '''chmod +x ./gradlew
./gradlew build'''
      }
    }
    stage('Collect Aritfacts') {
      steps {
        archiveArtifacts 'build/exe/main/*.exe'
      }
    }
  }
}