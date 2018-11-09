pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh '''chmod +x ./gradlew
./gradlew build -Pbuildnumber=${BUILD_NUMBER}""'''
      }
    }
    stage('Collect Aritfacts') {
      steps {
        archiveArtifacts 'build/exe/main/*'
      }
    }
  }
}