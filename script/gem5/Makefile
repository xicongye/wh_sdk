gem5-install:
	sudo apt install build-essential git m4 scons zlib1g zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev python-dev python
	sudo pip install pydot
	sudo apt install graphviz
	git clone https://gem5.googlesource.com/public/gem5
	cd gem5; scons build/RISCV/gem5.opt -j$$(nproc)
	cd gem5/util/term; make

