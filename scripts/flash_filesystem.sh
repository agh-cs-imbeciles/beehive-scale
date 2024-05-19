
source scripts/.env
mkdir -p tmp
${MKSPIFFS}/mkspiffs -c config -b 4096 -p 256 -s 0x160000 tmp/spiffs.bin
python3 ${ESPTOOL}/esptool.py \
  --chip esp32 \
  --port ${PORT} \
  --baud 115200 \
  write_flash \
  -z 0x290000 \
  tmp/spiffs.bin
rm -f tmp/spiffs.bin
