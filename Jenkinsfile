pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        sh '''

mkdir /opt/tomcat/.gradle/
chmod +x /opt/tomcat/.gradle/
chmod +x ./gradlew
./gradlew build'''
      }
    }
    stage('Collect Aritfacts') {
      steps {
        archiveArtifacts 'Gridbot'
      }
    }
  }
}