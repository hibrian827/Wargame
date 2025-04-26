// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import { ERC20 } from "@openzeppelin/contracts/token/ERC20/ERC20.sol";
import { Ownable } from "@openzeppelin/contracts/access/Ownable.sol";

contract HTOToken is ERC20, Ownable {
    constructor() ERC20("HTO Token", "HTO") Ownable(msg.sender) {
    }

    function mint(address sender, uint256 amount) external onlyOwner {
        _mint(sender, amount);
    }
}
