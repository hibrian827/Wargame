#!/bin/sh

anvil --host 0.0.0.0 --port 12455 --accounts 2 --balance 1 &
# Wait for Anvil to start
sleep 3

forge script script/Deploy.s.sol:DeployScript --rpc-url http://127.0.0.1:12455 --private-key 0xac0974bec39a17e36ba4a6b4d238ff944bacb478cbed5efcae784d7bf4f2ff80 --broadcast

tail -f /dev/null