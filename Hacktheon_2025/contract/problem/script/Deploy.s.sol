// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import {Script} from "forge-std/Script.sol";
import "forge-std/console.sol";
import {WETH} from "../src/WETH.sol";
import {HTOToken} from "../src/HTOToken.sol";
import {DepositNFT} from "../src/DepositNFT.sol";
import {VestingNFT} from "../src/VestingNFT.sol";
import {YieldVault} from "../src/YieldVault.sol";
import {Swap} from "../src/Swap.sol";

contract DeployScript is Script {
    function run() public {
        vm.startBroadcast();
        WETH wETH = new WETH();
        console.log("wETH deployed at:", address(wETH));
        
        HTOToken htoToken = new HTOToken();
        console.log("HTOToken deployed at:", address(htoToken));

        
        DepositNFT depositNFT = new DepositNFT();
        console.log("DepositNFT deployed at:", address(depositNFT));

        
        VestingNFT vestingNFT = new VestingNFT();
        console.log("VestingNFT deployed at:", address(vestingNFT));
        
        YieldVault yieldVault = new YieldVault(
            address(wETH),
            address(htoToken),
            address(depositNFT),
            address(vestingNFT)
        );
        console.log("YieldVault deployed at:", address(yieldVault));

        wETH.mint(address(yieldVault), 255); 
        htoToken.mint(address(yieldVault), 340282366920938463463374607431768211455); 

        depositNFT.transferOwnership(address(yieldVault));
        vestingNFT.transferOwnership(address(yieldVault));

        Swap swap = new Swap(address(wETH), address(htoToken));
        console.log("Swap deployed at:", address(swap));

        wETH.mint(address(swap), 4294967295); 
        htoToken.mint(address(swap), 18446744073709551615); 

        vm.stopBroadcast();
    }
}
