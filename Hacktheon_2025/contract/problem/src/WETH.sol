// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;
import {Script} from "forge-std/Script.sol";
import "forge-std/console.sol";
import { ERC20 } from "@openzeppelin/contracts/token/ERC20/ERC20.sol";
import { Ownable } from "@openzeppelin/contracts/access/Ownable.sol";

contract WETH is ERC20, Ownable {
    constructor() ERC20("Wrapping ETH", "WETH") Ownable(msg.sender) {
    }

    function mint(address sender, uint256 amount) external onlyOwner {
        _mint(sender, amount);
    }

    function flag() external returns (string memory) {
        if(this.balanceOf(msg.sender) > 100000000) {
            _burn(msg.sender, 100000000);
            return "FLAG{THIS_IS_FAKE_FLAG}";
        }
        return "";
    }
}
