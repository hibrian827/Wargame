// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.20;

import { IERC20 } from "@openzeppelin/contracts/token/ERC20/IERC20.sol";
import { ReentrancyGuard } from "@openzeppelin/contracts/utils/ReentrancyGuard.sol";

import { WETH } from "./WETH.sol";
import { HTOToken } from "./HTOToken.sol";

interface IUniswapV2Callee {
  function uniswapV2Call(address sender, uint amount0Out, uint amount1Out, bytes calldata data) external;
}

contract Swap is ReentrancyGuard {
  WETH public wETH; 
  HTOToken public htoToken;

  constructor(address _wETH, address _htoToken) {
    wETH = WETH(_wETH);
    htoToken = HTOToken(_htoToken);
  }

  function _getExchange(uint amount0Out, uint amount1Out) public returns (uint) {
    return amount0Out != 0 ? amount0Out * 2 : amount1Out / 2; 
  }

  function swap(uint amount0Out, uint amount1Out, address to, bytes calldata data) external nonReentrant {
    address _from;
    address _to;
    uint _amount;

    if (amount0Out != 0) {
      _from = address(wETH);
      _to = address(htoToken);
      _amount = amount0Out;
    } else {
      _to = address(wETH);
      _from = address(htoToken);
      _amount = amount1Out;
    }

    if (data.length == 0) {
      IERC20(_to).transfer(to, _getExchange(amount0Out, amount1Out));
      IERC20(_from).transferFrom(to, address(this), _amount);
    } else {
      uint balanceBefore = IERC20(_from).balanceOf(address(this));

      IERC20(_from).transfer(to, _amount);
  
      IUniswapV2Callee(to).uniswapV2Call(to, amount0Out, amount1Out, data);

      uint balanceAfter = IERC20(_from).balanceOf(address(this));

      require(balanceAfter >= balanceBefore);
    }
  }
}
