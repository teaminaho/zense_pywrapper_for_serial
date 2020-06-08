 #!/bin/sh
 python -c "from zense_pywrapper_for_serial import PyPicoZenseModuleForSerial; zense_mng = PyPicoZenseModuleForSerial(0); zense_mng.getSerialNumber(); del zense_mng"
