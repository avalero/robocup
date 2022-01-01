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


Run with the command
```
  rcssmonitor
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

Cobfigure library path

```
  sudo nano /etc/ld.so.conf.d/robocup.conf
  //add one line  /usr/lobal/lib
  //save and exit ctrl+o ctrl+x
  sudo ldconfig
```
Run with the command
```
  rcssserver
```
