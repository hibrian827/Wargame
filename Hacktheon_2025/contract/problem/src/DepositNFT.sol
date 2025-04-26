// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import { ERC721 } from "@openzeppelin/contracts/token/ERC721/ERC721.sol";
import { Ownable } from "@openzeppelin/contracts/access/Ownable.sol";

contract DepositNFT is ERC721, Ownable {
    constructor() ERC721("Deposit NFT", "DNFT") Ownable(msg.sender) {
    }

    function mint(address sender, uint256 amount) external onlyOwner {
        _safeMint(sender, amount);
    }
}
