# Stokvel Coin
Stokvel Coin is a crypto currency based on EOS blockchain, 

## How to get started with setting up EOSIO development environment.

### Install EOSIO

  wget https://github.com/eosio/eos/releases/download/v2.1.0/eosio_2.1.0-1-ubuntu-20.04_amd64.deb
  
  sudo apt install ./eosio_2.1.0-1-ubuntu-20.04_amd64.deb

  wget https://github.com/eosio/eosio.cdt/releases/download/v1.8.0/eosio.cdt_1.8.0-1-ubuntu-18.04_amd64.deb
  
  sudo apt install ./eosio.cdt_1.8.0-1-ubuntu-18.04_amd64.deb

### Test nodeos - EOSIO 
nodeos -e -p eosio --hard-replay --plugin eosio::producer_plugin --plugin eosio::chain_api_plugin --plugin eosio::http_plugin --plugin eosio::history_plugin --plugin eosio::history_api_plugin --access-control-allow-origin='*' --contracts-console --http-validate-host=false --verbose-http-errors >> nodeos.log 2>&1 &

### List wallet list.
cleos wallet list

	Wallets:
	
	[]

### Create a wallet called "wallet"
cleos wallet create --to-console -n wallet

	Creating wallet: wallet
	Save password to use in the future to unlock this wallet.
	Without password imported keys will not be retrievable.
	"PW5HsrEympm..........xMo5Vcphuk9EQNJzHEiaeV.........."

cleos wallet list

	Wallets:
	[
	  "wallet *"
	]

### Open the wallet we just created
cleos wallet open -n wallet

	Opened: wallet

### Unlock the wallet if not already unlocked.
cleos wallet unlock -n wallet

	password: Unlocked: wallet

cleos wallet list

	cleos wallet list
	Wallets:
	[
	  "wallet *"
	]

### Check keys inside the wallet
cleos wallet keys

	[]

### EOS create keys for the wallet
cleos create key --to-console

	Private key: 5Jnh.....bSPt5dgga44g6..........XGBzPyDUbpFwyStiqSF
	Public key: EOS53tLdbZejRBU..........VQqDcAsbNvCs.....qtGJwPd9iq7


### Import the private key to the wallet
cleos wallet import -n wallet --private-key 5Jn..........5dgga..........5t1FXGBzPyDUbpFwyStiqSF

	imported private key for: E..........jRBU235og3wHijVQqDcAsbNvCs..........Pd9iq7

cleos wallet keys

	[
	  "E..........jRBU235og3wHijVQqDcAsbNvCs..........Pd9iq7"
	]

### Close the wallet
cleos wallet private_keys -n wallet --password PW5HsrEympm8nst..................mjRYRh4V5X

	[[
	    "EOS53tLdbZe...................................Pd9iq7",
	    "5Jnhs1oUcbSP.........................PyDUbpFwyStiqSF"
	  ]
	]


### To create an account we need to have an existing account.
#### So we need to import the EOS default account into our wallet.
cleos wallet import -n wallet --private-key 5KQwrPbwdL6Ph......................eyXtP79zkvFD3

##### Create our first user account. We are going to use the default eosio account, the name of our account is going to be stokvelacc.
cleos create account eosio stokvelacc EOS53tLdbZe............................WLqtGJwPd9iq7

	Failed to connect to nodeos at http://127.0.0.1:8888/; is nodeos running?
	
nodeos -e -p eosio --hard-replay --plugin eosio::producer_plugin --plugin eosio::chain_api_plugin --plugin eosio::http_plugin --plugin eosio::history_plugin --plugin eosio::history_api_plugin --access-control-allow-origin='*' --contracts-console --http-validate-host=false --verbose-http-errors >> nodeos.log 2>&1 &

cleos create account eosio stokvelacc EOS53tLdbZ...............................GJwPd9iq7

	executed transaction: dab0f0c98a21d53de62182639fc644d56bc2d099d51b15aa3e19c17d9cc96b29  200 bytes  23914 us
	eosio <= eosio::newaccount            {"creator":"eosio","name":"stokvelacc","owner":{"threshold":1,"keys":[{"key":"EOS53tLdbZejRBU235og3w...
	warning: transaction executed locally, but may not be confirmed by the network yetult         ]

	Our transaction harsh is dab0f0c98a21d53de62182639fc644d56bc2d099d51b15aa3e19c17d9cc96b29
	Details of the transaction are eosio <= eosio::newaccount            {"creator":"eosio","name":"stokvelacc","owner":{"threshold":1,"keys":[{"key":"EOS53tLdbZejRBU235og3w...

### Lets view our account.
#### There are 2 types of default permisions i.e Owner and Active.
#### The memory quota is unlimited on the testnet, the quotas for cpu, net and memory is function of coins being staked in the mainnet.
cleos get account stokvelacc

	created: 2021-09-12T11:22:06.500
	permissions: 
     		owner     	1:    1 EOS53tLdbZejRB....................LqtGJwPd9iq7
        	active     	1:    1 EOS53tLdbZe..............................WLqtGJwPd9iq7
	memory: 
     		quota:       unlimited  used:      2.66 KiB  

	net bandwidth: 
     		used:               unlimited
     		available:          unlimited
     		limit:              unlimited

	cpu bandwidth:
     		used:               unlimited
     		available:          unlimited
     		limit:              unlimited

### Changing owner account keys. Change the keys for owner permision.

cleos create key --to-console

	Private key: 5JzHj66t...................................ccj5FokV9
	
	Public key: EOS8VeWVx................................6cco1vCwSXJywJ

cleos wallet import -n wallet --private-key 5JzHj66tJ...............................cj5FokV9

	imported private key for: EOS8VeWVx9Z............................q6cco1vCwSXJywJ

### Change owner permission
cleos set account permission stokvelacc owner EOS8VeWV.................................CwSXJywJ -p stokvelacc@owner

	executed transaction: b2b787c32dca439fa3a8ca6a863dc85f287091a3b5b02813f070196e30f39dcc  160 bytes  209 us
	
	# eosio <= eosio::updateauth {"account":"stokvelacc","permission":"owner","parent":"","auth":{"threshold":1,"keys":[{"key":"EOS8V...
	warning: transaction executed locally, but may not be confirmed by the network yetult         ]

cleos get account stokvelacc

	
## Compile and Deploy project code

### Compile Token
#### To build the newt token run the following commands from command shell:
     eosio-cpp -abigen -abigen_output=eosio.stokvel.token.abi -o eosio.stokvel.token.wasm eosio.stokvel.token.cpp

#### You can now deploy the newt.wasm on the blockchain. To do so run the following command:
cleos set contract eosio.stokvel.token . --abi eosio.stokvel.token.abi eosio.stokvel.token.wasm -p eosio.stokvel.token@active

##### Project Founder: Phumlani Mbabela
