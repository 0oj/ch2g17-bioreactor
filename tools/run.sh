# run server.py and api/every_second.py as background processes
# kill these processes when the script exits
sh tools/clearlogs.sh
python server.py &
python api/every_second.py &
trap "kill 0" EXIT
wait
