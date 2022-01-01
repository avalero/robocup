# robocup

## Install Monitor and Server

Install dependencies

```
 sudo apt install build-essential libboost-all-dev qt5-default libfontconfig1-dev libaudio-dev libxt-dev libglib2.0-dev libxi-dev libxrender-dev flex bison git 
```

### rcssmonitor

Clone the repository

```
  git clone git@github.com:rcsoccersim/rcssmonitor.git
```

Go into de directory

```
  cd rcssmonitor
```

Execute build commands

```
  autoreconf -i
  ./configure
  make
  sudo make install
```

### rcssserver

Get release and uncompress

```
  wget https://github.com/rcsoccersim/rcssserver/releases/download/rcssserver-16.0.1/rcssserver-16.0.1.tar.gz
  tar xvfz rcssserver-16.0.1.tar.gz 
``` 

Go into the directory

```
  cd cd rcssserver-16.0.1
```

Execute build commands

``` 
  ./configure
  make
  sudo make insall
```

