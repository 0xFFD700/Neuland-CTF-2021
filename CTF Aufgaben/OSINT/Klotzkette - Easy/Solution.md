# Klotzkette - Solution

For this challenge you received a challenge text and a PNG-file. The image 
depictures a Matrix-style avatar of some sort. We might already recognize this
as an Reddit avatar, and with the filename we notice a user /u/IvanKalashnik.
You can already do a reverse image search on Google on the avatar and it should
bring you to the same site.

Ivan Kalashnik has one posting on Reddit, an obvious ethereum "giveaway" scam.
There he mentions a wallet address: `0x00Bfeb18489e4437f11c3594aaDcf56Cad9Fa458`.

We pull over to the Ethereum Blockchain Explorer[^1], search for the address and 
find exactly ... *zero* transactions. Damn it! 

But wait, there was a hint in the reddit thread. Ivan tells us something about 
a mainnet (crossed out). Indeed, there is a button that searches for 
transactions on other chains besides the mainnet and curiously, there is one 
transaction on Ropsten, the PoW testnet.

We inspect the transaction but nothing shows up immediately. However, the 
transferred amount is weird. 0.00 Ether? Why would Ivan pay for gas, if he has 
no value to transfer? We do some research and learn, that you mostly see such 
transactions to trigger a smart contract with some input data. Etherscan shows
us the input data if we expand the view and indeed, there is some input data 
there. Now we only need to decode the hex-data as an ASCII string and we 
successfully retrieved the flag.

[^1]: https://etherscan.io/
