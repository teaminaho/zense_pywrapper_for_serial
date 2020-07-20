.PHONY: build
build:
	sudo docker build -t zense_pywrapper_for_serial_v3 .

.PHONY: run
run:
	xhost + local:root
	sudo docker run -it \
    --network="host" \
	--env=DISPLAY=$(DISPLAY) \
	--env=QT_X11_NO_MITSHM=1 \
	--privileged \
	--mount type=bind,src=/dev,dst=/dev,readonly \
	--mount type=bind,src=`pwd`/scripts,dst=/app/scripts \
	--mount type=bind,src=`pwd`/src,dst=/app/src \
	--volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
	 zense_pywrapper_for_serial_v3 /bin/bash