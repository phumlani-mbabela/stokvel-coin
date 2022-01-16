# Stokvel Coin
Stokvel Coin is a crypto currency based on EOS blockchain, 

# What is a Stokvel

A Stokvel is an investment club. Usually you become a member by invitation-only, members of a Stokvel often belong to a close knit community. Stokvels are formally defined as a type of a investment club in which a group of people enter into an agreement to contribute a fixed amount of money to a common pool either weekly, fortnightly or monthly. A Stokvel serves as a rotating credit union or saving schemes where members contribute fixed sums of money to a central fund on a particular basis. Stokvels are not uniquely a South African phenomenon, you get them in various forms, such as Burial Societies, Investment Clubs, Umgalelo Clubs, Mavuso Stokvel and Youth Stokvels. Stokvels are not regulated by the South African financial regulators unlike Banks and Insurance companies, hence they are not thought of as part of the formal financial business sector. Stokvel are governed by agreed upon rules and regulations that are part of its constitution(founding document), there is no legal protection offered by financial regulators.

There are a number of pain points in the Stokvel Business Model.

* The periodic(weekly, fortnightly or monthly) contributions are compulsory and skipping contributions can tantamount to membership cancellation.
* The periodic contributions often have a hard cutoff date that no member is allowed to miss, missing a payment tantamount to disqualification. This is a huge problem that invariably lead to conflicts between members.
* Some Stokvels don't allow members to join after the commencement date, the commencement date is usually the first month of the year.
* Barriers to Digital transformation are prevalent in the informal economy.

This research project is geared to investigate how the Stokvel Business model can be implemented using Blockchains, Ricardian and Smart Contracts.



## Software Installation
### Below are instructions for downloading and installing the software needed.
  * sudo yum update
  * wget https://github.com/eosio/eos/releases/download/v2.2.0-rc1/eosio-2.2.0-rc1.el7.x86_64.rpm
  * sudo yum install ./eosio-2.2.0-rc1.el7.x86_64.rpm
  * wget https://github.com/EOSIO/eosio.cdt/releases/download/v1.8.1/eosio.cdt-1.8.1-1.amzn.x86_64.rpm
  * sudo yum install $eosio.cdt-1.8.1-1.amzn.x86_64.rpm

### Install the Stokfel Token and Contract.
  * sudo mkdir -p /opt/stokvel-coin/code
  * sudo chown ec2-user:ec2-user -R /opt/stokvel-coin/
  * sudo yum install -y git
  * cd /opt/stokvel-coin/code
  * git clone https://github.com/phumlani-mbabela/stokvel-coin.git
  * sudo mkdir -p /opt/stokvel-coin/code/stokvel-coin/secrets/
  * sudo chown ec2-user:ec2-user -R /opt/stokvel-coin/
  
### Create a service startup script[Optional].This file is available in the code repo.
  * sudo vi /etc/systemd/system/eosio.service
  * ...  ...
  * sudo systemctl daemon-reload
  * sudo systemctl enable eosio.service
  * sudo systemctl reboot

## Blockchain Testing
### Below are instructions for starting and testing the blockchain.
  * Start server - sudo nodeos -e -p eosio --p2p-peer-address=0.0.0.0:9876 --plugin eosio::net_api_plugin --plugin eosio::net_plugin --plugin eosio::producer_plugin --plugin eosio::producer_api_plugin --plugin eosio::chain_api_plugin --plugin eosio::http_plugin --plugin eosio::history_plugin --plugin eosio::history_api_plugin --filter-on="*" --access-control-allow-origin='*' --contracts-console --http-validate-host=false --verbose-http-errors --replay-blockchain  > /var/log/eosio-startup.out 2>&1 
  * View the blockchain process - sudo ps -eaf | grep nodeos
  * View logs - tail -f /var/log/eosio-startup.out
  *  Protocol Features - curl --request POST --url http://127.0.0.1:8888/v1/producer/schedule_protocol_feature_activations -d '{"protocol_features_to_activate": ["0ec7e080177b2c02b278d5088611686b49d739925a92d9bfcacd7fc6b74053bd"]}'
  * Get system information - cleos --url http://13.245.150.240:8888  get info


## Accounts Configuration
### Setup Wallets
* cleos wallet create -n w_admin -f /opt/stokvel-coin/code/stokvel-coin/secrets/w_admin.pwd   
* cleos wallet create -n w_anele -f /opt/stokvel-coin/code/stokvel-coin/secrets/w_anele.pwd   
* cleos wallet create -n w_alice -f /opt/stokvel-coin/code/stokvel-coin/secrets/w_alice.pwd   
* cleos wallet create -n w_thabo -f /opt/stokvel-coin/code/stokvel-coin/secrets/w_thabo.pwd   
* cleos wallet create -n w_james -f /opt/stokvel-coin/code/stokvel-coin/secrets/w_james.pwd   
* cleos wallet create            -f /opt/stokvel-coin/code/stokvel-coin/secrets/w_default.pwd 

### Create keys
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_admin.txt 
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_admin1.txt 
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_anele.txt 
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_alice.txt 
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_thabo.txt 
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_james.txt 
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_default.txt 
* cleos create key --file /opt/stokvel-coin/code/stokvel-coin/secrets/keys_default1.txt 

### Import keys to the corresponding wallets.
* cleos wallet open 
* cleos wallet unlock --password PW5JzxxNgSGEubmxBT6hiWZbtURpL6kkfyfgkjY7n36XAYRdqjc8Z 
* cleos wallet import --private-key 5J6jJNEi7x8uH77kUBuZmcVmSZ9vDustnCigDcAv9E7ewzmHvf1 
* cleos wallet import --private-key 5J4ESvWknUcKsdFQfBDcY7j5hD5FED7r26zFod8fGBPrwT3Cqwh 

* cleos wallet open -n w_admin 
* cleos wallet unlock -n w_admin --password PW5Jf5J9drtA39FMgJ2FqrKikudxY6XVFD9YebyFGhhMCb2Kqbyus 
* cleos wallet import --name w_admin --private-key 5JSxZAGFnyT9rfUbnZBRLWrhYSUssjyZLRHJnnCoqSogPuq89C9 
* cleos wallet import --name w_admin --private-key 5JSxZAGFnyT9rfUbnZBRLWrhYSUssjyZLRHJnnCoqSogPuq89C9 

* cleos wallet open -n w_anele 
* cleos wallet unlock -n w_anele --password PW5K1i3ka9ctFpX8n1ADHojtA7CZtd1pYpJPry6UNQ7udKLxNooEM 
* cleos wallet import --name w_anele --private-key 5JTmMUrfc9iujY7mmh3LBjZCwB88qxoiM5qiHnipgG6DPww5G8Q 

* cleos wallet open -n w_alice 
* cleos wallet unlock -n w_alice --password PW5KHdAMqNREGnrZPnggi8FFADgFaR4NTbf8UBjxdWxsk3CsEzQM5 
* cleos wallet import --name w_alice --private-key 5J2g8LarmhHd2PjyWzTEVaZiXDPqwBS3Dg3VJmWQyTnJ5vhv8CB 

* cleos wallet open -n w_thabo 
* cleos wallet unlock -n w_thabo --password PW5KG3EvAvosExvADsYyRpHghJTEKNbE7dgQVPY8RjLEGDD54Zjbu 
* cleos wallet import --name w_thabo --private-key 5HwXyKDF7PMF9VSj7JJJ74JRAzR5NaUmfxJScBXm5LxU4sez7Ck 

* cleos wallet open -n w_james
* cleos wallet unlock -n w_james --password PW5JTVwsPJCiLp5fY9HGM5HEPcmw6J6t9PU7J123XgKb1cPgvtKHp
* cleos wallet import --name w_james --private-key 5KC5Mu4pK1ewDPHALdG99n8d8DWufMQnaaabws6hSmYroLopKmX

### Import the eosio default private key.
* cleos wallet import                --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD  
* cleos wallet import --name w_admin --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 
* cleos wallet import --name w_anele --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 
* cleos wallet import --name w_alice --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 
* cleos wallet import --name w_thabo --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 
* cleos wallet import --name w_james --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 


### Create accounts
* cleos create account eosio accadmin EOS78EE82iFKgZtg6PdY9wv8R5Jp19x1oEf931NR2A2B75yJYJjnm EOS62PqFepS9PwH41wwYLCK9pxTj6vbRbUW6EY8EA56abudxZdayB -p eosio@active
* cleos create account eosio accanele EOS8QR2MvXR6vRgeACNX2KRc5iToRdm7ZAjXFvgAPxZ1z5FSNrepa EOS8QR2MvXR6vRgeACNX2KRc5iToRdm7ZAjXFvgAPxZ1z5FSNrepa -p eosio@active 
* cleos create account eosio accalice EOS8WL6ipyQWGFo3vAHE43SoHArj9mwJ2j3XRVRUrhcx3U8eFU9n4 EOS8WL6ipyQWGFo3vAHE43SoHArj9mwJ2j3XRVRUrhcx3U8eFU9n4 -p eosio@active 
* cleos create account eosio accthabo EOS8MV5EqvYJXNBKRkEE5Yp3KLQdQwnFA63ZZLADJDHnz7D4GkaTj EOS8MV5EqvYJXNBKRkEE5Yp3KLQdQwnFA63ZZLADJDHnz7D4GkaTj -p eosio@active  
* cleos create account eosio accjames EOS5mcL66PowDxrv9TypzXkQsnoonJEnEdFJUK1Mg94WK9k5xExkj EOS5mcL66PowDxrv9TypzXkQsnoonJEnEdFJUK1Mg94WK9k5xExkj -p eosio@active 

### Test Accounts
* cleos get account accadmin --json
* cleos get account accanele --json
* cleos get account accalice --json
* cleos get account accthabo --json
* cleos get account accjames --json


## Compile and Deploy the code

### Compile the token contract
* cd /opt/stokvel-coin/code/stokvel-coin/eosiostokveltoken/build
* eosio-cpp -abigen ../src/eosiostokveltoken.cpp  -o eosiostokveltoken.wasm -I ../include/
* cd /opt/stokvel-coin/code/stokvel-coin/bank/build
* eosio-cpp -abigen ../src/bank.cpp  -o bank.wasm -I ../include/
  
### Deploy the token contract
* cd /opt/stokvel-coin/code/stokvel-coin/bank/build
* cleos set contract accadmin . --abi eosiostokveltoken.abi eosiostokveltoken.wasm -p accadmin@active

## Create a new token
To create the STVL token use the following command:
The create action mints 21 million tokens.
    * cleos push action accadmin createe '["accadmin","210000000000.0000 STVL", "created 210000000000.0000 STVL"]' -p accadmin@active
### Alternative invocation
    * cleos push action accadmin create '[]' -p accadmin@active
    
### View the newly created token.
    * cleos get table accadmin STVL stat        
    * cleos get currency stats accadmin STVL

## Issue New Tokens
### Issue 100 STVL tokens. To execute the action, use the following command:
    * cleos push action accadmin issue '["210000000000.0000 STVL", "issue 210000000000 STVL"]' -p accadmin@active
    * cleos push action accadmin issuee '["accadmin", "210000000000.0000 STVL", "issued 210000000000 STVL"]' -p accadmin@active
    * cleos get table accadmin STVL stat
          
## Transfer tokens from the suspense account to a different account.
    * cleos push action accadmin transfer '[ "accadmin", "accanele", "101.0101 STVL", "Transfer 101 STVL tokens from suspense account." ]' -p accadmin@active
    * cleos push action accadmin transfer '[ "accadmin", "accalice", "102.0202 STVL", "Transfer 102 STVL tokens from suspense account." ]' -p accadmin@active
    * cleos push action accadmin transfer '[ "accadmin", "accthabo", "103.0303 STVL", "Transfer 103 STVL tokens from suspense account." ]' -p accadmin@active
    * cleos push action accadmin transfer '[ "accadmin", "accjames", "104.0404 STVL", "Transfer 104 STVL tokens from suspense account." ]' -p accadmin@active
### Alternative invocation.
    * cleos transfer accadmin accjames "202.0202 STVL" "Transfer 202 STVL tokens from suspense account." -c accadmin -p accadmin

## Inspect balances.
    * cleos get currency balance accadmin accadmin STVL
    * cleos get currency balance accadmin accanele STVL
    * cleos get currency balance accadmin accalice STVL
    * cleos get currency balance accadmin accthabo STVL
    * cleos get currency balance accadmin accjames STVL
### Alternative invocation.
    * cleos get account accadmin --json
    * cleos get account accanele --json
    * cleos get account accalice --json
    * cleos get account accthabo --json
    * cleos get account accjames --json

## Airgrab tokens
    * cleos push action accadmin airgrab '[ "accanele"]' -p accanele@active
    * cleos push action accadmin airgrab '[ "accanele", "100.0000 STVL"]' -p accanele@active
    * cleos get currency balance accadmin accanele STVL

##### Project Founder: Phumlani Kaida Mbabela