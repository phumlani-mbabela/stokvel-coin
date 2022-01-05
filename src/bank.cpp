/**
 * @name bank
 * @dev detect that one transfer EOS token to account deployed this contract and record its amount in the multi-index table
 * @version eosio.cdt v1.4.1
**/

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/action.hpp>
#include <eosio.token/bank.hpp>

namespace eosio {

using std::string;

void bank::deposit( name from, name to, asset quantity, string memo ) {
    if ( to == _self && from != _self ) {
        add_deposit( from, quantity );
    } else if ( from == _self && to != _self ) {
        asset total_amount = get_total_deposit( quantity.symbol );
        asset current_amount = get_current_balance( quantity.symbol );
        eosio_assert(total_amount <= current_amount, "this contract must remain at least total deposit");
    }
}

void bank::withdraw( name user, asset quantity ) {
    require_auth( user );
    eosio_assert( quantity.symbol == symbol("EOS", 4), "symbol must be EOS" );
    eosio_assert( quantity.amount > 0, "'quantity' should be positive" );
    sub_deposit( user, quantity );

    string message = "execute as inline action in withdraw of " + _self.to_string();
    transfer_to( user, quantity, message );
}

void bank::add_deposit( name user, asset quantity ) {
    if ( quantity.amount <= 0 ) {
        return;
    }

    deposit_index deposit_table( _self, user.value );
    auto deposit_data = deposit_table.find( quantity.symbol.code().raw() );

    if( deposit_data == deposit_table.end() ) {
        deposit_table.emplace( _self, [&]( auto& data ) {
            data.balance = quantity;
        });
    } else {
        asset deposit = deposit_data->balance;
        eosio_assert(deposit.symbol == quantity.symbol, "different symbol or precision mismatch from token of total deposit");

        deposit_table.modify( deposit_data, _self, [&]( auto& data ) {
            data.balance += quantity;
        });
    }

    auto total_deposit_data = total_deposit_table.find( quantity.symbol.code().raw() );

    if( total_deposit_data == total_deposit_table.end() ) {
        total_deposit_table.emplace( _self, [&]( auto& data ) {
            data.balance = quantity;
        });
    } else {
        asset deposit = total_deposit_data->balance;
        eosio_assert(deposit.symbol == quantity.symbol, "different symbol or precision mismatch from your token deposited");

        total_deposit_table.modify( total_deposit_data, _self, [&]( auto& data ) {
            data.balance += quantity;
        });
    }
}

void bank::sub_deposit( name user, asset quantity ) {
    if ( quantity.amount <= 0 ) {
        return;
    }

    deposit_index deposit_table( _self, user.value );
    auto deposit_data = deposit_table.find( quantity.symbol.code().raw() );
    eosio_assert(deposit_data != deposit_table.end(), "do not exist your data");

    asset deposit = deposit_data->balance;
    eosio_assert(deposit.symbol == quantity.symbol, "invalid your deposit symbol");
    eosio_assert(deposit.amount >= quantity.amount, "exceed the withdrawable amount");

    if ( deposit == quantity ) {
        deposit_table.erase( deposit_data );
    } else {
        deposit_table.modify( deposit_data, _self, [&]( auto& data ) {
            data.balance -= quantity;
        });
    }

    auto total_deposit_data = total_deposit_table.find( quantity.symbol.code().raw() );
    eosio_assert(total_deposit_data != total_deposit_table.end(), "do not exist total deposit data");

    asset total_deposit = total_deposit_data->balance;
    eosio_assert(total_deposit.symbol == quantity.symbol, "invalid total deposit symbol");
    eosio_assert(total_deposit.amount >= quantity.amount, "total deposit table is broken");

    if ( total_deposit == quantity ) {
        total_deposit_table.erase( total_deposit_data );
    } else {
        total_deposit_table.modify( total_deposit_data, _self, [&]( auto& data ) {
            data.balance -= quantity;
        });
    }
}

asset bank::get_total_deposit( symbol sym ) {
    auto total_deposit_data = total_deposit_table.find( sym.code().raw() );
    asset total_amount = { 0, sym };

    if ( total_deposit_data != total_deposit_table.end() ) {
        total_amount = total_deposit_data->balance;
    }

    return total_amount;
}

asset bank::get_current_balance( symbol sym ) {
    account_index account_table( name("eosio.stokvel.token"), _self.value );
    auto account_data = account_table.find( sym.code().raw() );
    asset current_amount = { 0, sym };

    if ( account_data != account_table.end() ) {
        current_amount = account_data->balance;
    }

    return current_amount;
}


void bank::transfer_to( name user, asset quantity, string message ) {
    /// execute "transfer" action (third arg)
    /// defined in "eosio.stokvel.token" account (second arg)
    /// passing its arguments by tuple (fourth arg)
    /// using this account's active permission (first arg)
    action(
        permission_level{ _self, name("active") },
        name("eosio.stokvel.token"),
        name("transfer"),
        std::make_tuple( _self, user, quantity, message )
    ).send();
}

/// dispatcher
extern "C" {
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
        if ( code == name("eosio.stokvel.token").value ) {
            if ( action == name("transfer").value ) {
                /// After one call eosio.stokvel.token::transfer action to this contract,
                /// bank::transfereos action is also executed.
                execute_action( name(receiver), name(code), &bank::deposit );
            }
        } else if ( code == receiver ) {
            if ( action == name("withdraw").value ) {
                execute_action( name(receiver), name(code), &bank::withdraw );
            }
        }
    }
}

} //namespace eosio
