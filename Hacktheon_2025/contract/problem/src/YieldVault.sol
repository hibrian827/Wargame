// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import { WETH } from "./WETH.sol";
import { HTOToken } from "./HTOToken.sol";
import { DepositNFT } from "./DepositNFT.sol";
import { VestingNFT } from "./VestingNFT.sol";
import { ReentrancyGuard } from "@openzeppelin/contracts/utils/ReentrancyGuard.sol";

contract YieldVault is ReentrancyGuard {
  struct Deposit {
    bool alive;
    uint256 depositAmount;
    uint64 endTimestamp;
  }
  Deposit[] internal deposits;

  struct Vesting {
    uint256 depositId;
    uint64 lastRewardedTimestamp;
  }
  Vesting[] internal vestings;

  WETH public wETH;
  HTOToken public htoToken;
  DepositNFT public depositNft;
  VestingNFT public vestingNft;

  constructor(address _wETH, address _htoToken, address _depositNft, address _vestingNft) {
    wETH = WETH(_wETH);
    htoToken = HTOToken(_htoToken);
    depositNft = DepositNFT(_depositNft);
    vestingNft = VestingNFT(_vestingNft);
  }

  function deposit(uint256 _depositAmount) external nonReentrant {
    wETH.transferFrom(msg.sender, address(this), _depositAmount);

    deposits.push(
      Deposit({
        alive: true,
        depositAmount: _depositAmount,
        endTimestamp: uint64(block.timestamp) + 1666551940
      })
    );
    uint256 _depositId = deposits.length - 1;
    depositNft.mint(msg.sender, _depositId);

    vestings.push(
      Vesting({
        depositId: _depositId,
        lastRewardedTimestamp: 0
      })
    );
    uint256 _vestingId = vestings.length - 1;
    vestingNft.mint(msg.sender, _vestingId);
  }

  function vesting(uint256 _vestingId) external nonReentrant {
    require(vestingNft.ownerOf(_vestingId) == msg.sender);
    require(_vestingId < vestings.length);

    Vesting memory _vesting = vestings[_vestingId];
    Deposit memory _deposit = deposits[_vesting.depositId];
    require(_deposit.alive);

    uint256 _reward = (_deposit.depositAmount * (uint64(block.timestamp) - _vesting.lastRewardedTimestamp)) / 1000;
    htoToken.transfer(msg.sender, _reward);
    _deposit.endTimestamp = uint64(block.timestamp) + 1666551940;
    _vesting.lastRewardedTimestamp = uint64(block.timestamp);
  }

  function withdraw(uint256 _depositId, bool force) external nonReentrant {
    require(depositNft.ownerOf(_depositId) == msg.sender);

    Deposit memory _deposit = deposits[_depositId];
    require(_deposit.alive);

    uint256 reward = _deposit.depositAmount;

    if (!force) {
      uint64 currentTimestamp = uint64(block.timestamp);
      require(currentTimestamp > _deposit.endTimestamp);
      htoToken.transfer(msg.sender, reward);
    }

    wETH.transfer(msg.sender, reward);
    _deposit.alive = false;
  }
}
