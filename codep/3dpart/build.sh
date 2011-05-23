INSTALL_DIR=$PWD

tar xvf lame-3.98.4.tar.bz2
cd lame-3.98.4
configure  --prefix=$INSTALL_DIR/install
make


cd $INSTALL_DIR
tar xvf bzip2-1.0.5.tar.bz2
cd bzip2-1.0.5
make
make -n install  PREFIX=$INSTALL_DIR/install


cd $INSTALL_DIR
tar xvf libogg-1.1.3.tar.gz
cd libogg-1.1.3
configure  --prefix=$INSTALL_DIR/install
make
 

cd $INSTALL_DIR

