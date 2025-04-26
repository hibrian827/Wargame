// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import { ERC721 } from "@openzeppelin/contracts/token/ERC721/ERC721.sol";
import { Ownable } from "@openzeppelin/contracts/access/Ownable.sol";

contract VestingNFT is ERC721, Ownable {
    constructor() ERC721("Vesting NFT", "VNFT") Ownable(msg.sender) {
    }

    function mint(address sender, uint256 amount) external onlyOwner {
        _safeMint(sender, amount);
    }
}
