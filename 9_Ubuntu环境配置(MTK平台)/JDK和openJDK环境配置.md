


1�� ��װopenjdk-8:

```makefile
sudo add-apt-repository ppa:openjdk/ppa
sudo add-apt-repository ppa:openjdk-r/ppa
sudo apt-get update
sudo apt-get install openjdk-8-jdk

sudo chmod -R 755 /usr/lib/jvm/java-8-openjdk-amd64

sudo gedit ~/.bashrc

�ļ�ĩβ�������������Ϣ��

#for openJDK8:
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export JRE_HOME=/usr/lib/jvm/java-8-openjdk-amd64/jre
export PATH=$JAVA_HOME/bin:$JAVA_HOME/jre/bin:$PATH
export CLASSPATH=$CLASSPATH:.:$JAVA_HOME/lib:$JAVA_HOME/jre/lib

. ~/.bashrc

sudo update-alternatives --config java
sudo update-alternatives --config javac
ѡ����Ҫʹ�õ�JDK�汾��

ȷ��һ��·����
printenv JAVA_HOME
java -version

```

