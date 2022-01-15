#include <eosiostokveltoken.hpp>

namespace eosio {

	void token::Create(const name& issuer, const asset& maximum_supply) {
		require_auth(get_self());

		auto sym = maximum_supply.symbol;
		check(sym.is_valid(), "invalid symbol name");
		check(maximum_supply.is_valid(), "invalid supply");
		check(maximum_supply.amount > 0, "max-supply must be positive");

		stats statstable(get_self(), sym.code().raw());
		auto existing = statstable.find(sym.code().raw());
		check(existing == statstable.end(), "token with symbol already exists");

		statstable.emplace(get_self(), [&](auto& s) {
			s.supply.symbol = maximum_supply.symbol;
			s.max_supply = maximum_supply;
			s.issuer = issuer;
		});
	}

	void token::create() {
		require_auth(get_self());

		auto sym = symbol("STVL", 4); // STVL is the token symbol with precision 4
		auto maximum_supply = asset(210000000000, sym);

		stats statstable(get_self(), sym.code().raw());
		auto existing = statstable.find(sym.code().raw());
		check(existing == statstable.end(), "token with symbol already created");

		statstable.emplace(get_self(), [&](auto& s) {
			s.supply.symbol = sym;
			s.max_supply = maximum_supply;
			s.issuer = get_self();
		});
	}


	void token::Issue(const name& to, const asset& quantity, const string& memo) {
		auto sym = quantity.symbol;
		check(sym.is_valid(), "invalid symbol name");
		check(memo.size() <= 256, "memo has more than 256 bytes");

		stats statstable(get_self(), sym.code().raw());
		auto existing = statstable.find(sym.code().raw());
		check(existing != statstable.end(), "token with symbol does not exist, create token before issue");
		const auto& st = *existing;
		check(to == st.issuer, "tokens can only be issued to issuer account");

		require_auth(st.issuer);
		check(quantity.is_valid(), "invalid quantity");
		check(quantity.amount > 0, "must issue positive quantity");

		check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
		check(quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

		statstable.modify(st, same_payer, [&](auto& s) {
			s.supply += quantity;
		});

		add_balance(st.issuer, quantity, st.issuer);
	}

	void token::issue(const asset& quantity, const string& memo) {
		require_auth(get_self());

		auto sym = quantity.symbol;
		auto newtsym_code = symbol("STVL", 4); // STVL is the token symbol with precision 4
		check(sym.code() == newtsym_code.code(), "This contract can handle NEWT tokens only.");
		check(sym.is_valid(), "invalid symbol name");
		check(memo.size() <= 256, "memo has more than 256 bytes");

		stats statstable(get_self(), sym.code().raw());
		auto existing = statstable.find(sym.code().raw());
		check(existing != statstable.end(), "token with symbol does not exist, create token before issue");

		const auto& existing_token = *existing;
		require_auth(existing_token.issuer);

		check(quantity.is_valid(), "invalid quantity");
		check(quantity.amount > 0, "must issue positive quantity");
		check(quantity.symbol == existing_token.supply.symbol, "symbol precision mismatch");
		check(quantity.amount <= existing_token.max_supply.amount - existing_token.supply.amount,
			  "quantity exceeds available supply");

		statstable.modify(existing_token, same_payer, [&](auto& s) {
			s.supply += quantity;
		});

		add_balance(existing_token.issuer, quantity, existing_token.issuer);
	}

	void token::Retire(const asset& quantity, const string& memo) {
		auto sym = quantity.symbol;
		check(sym.is_valid(), "invalid symbol name");
		check(memo.size() <= 256, "memo has more than 256 bytes");

		stats statstable(get_self(), sym.code().raw());
		auto existing = statstable.find(sym.code().raw());
		check(existing != statstable.end(), "token with symbol does not exist");
		const auto& st = *existing;

		require_auth(st.issuer);
		check(quantity.is_valid(), "invalid quantity");
		check(quantity.amount > 0, "must retire positive quantity");

		check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");

		statstable.modify(st, same_payer, [&](auto& s) {
			s.supply -= quantity;
		});

		sub_balance(st.issuer, quantity);
	}

	void token::retire(const asset& quantity, const string& memo) {
		auto sym = quantity.symbol;
		check(sym.is_valid(), "invalid symbol name");
		check(memo.size() <= 256, "memo has more than 256 bytes");
		auto newtsym_code = symbol("STVL", 4); // STVL is the token symbol with precision 4
		check(sym.code() == newtsym_code.code(), "This contract can handle NEWT tokens only.");

		stats statstable(get_self(), sym.code().raw());
		auto existing = statstable.find(sym.code().raw());
		check(existing != statstable.end(), "token with symbol does not exist");
		const auto& st = *existing;

		require_auth(st.issuer);
		check(quantity.is_valid(), "invalid quantity");
		check(quantity.amount > 0, "must retire positive quantity");

		check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");

		statstable.modify(st, same_payer, [&](auto& s) {
			s.supply -= quantity;
		});

		sub_balance(st.issuer, quantity);
	}

	void token::Transfer(const name& from, const name& to, const asset& quantity, const string& memo) {
		check(from != to, "cannot transfer to self");
		require_auth(from);
		check(is_account(to), "to account does not exist");
		auto sym = quantity.symbol.code();
		stats statstable(get_self(), sym.raw());
		const auto& st = statstable.get(sym.raw(), "no balance with specified symbol");

		require_recipient(from);
		require_recipient(to);

		check(quantity.is_valid(), "invalid quantity");
		check(quantity.amount > 0, "must transfer positive quantity");
		check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
		check(memo.size() <= 256, "memo has more than 256 bytes");

		auto payer = has_auth(to) ? to : from;

		sub_balance(from, quantity);
		add_balance(to, quantity, payer);
	}

	void token::transfer(const name& from, const name& to, const asset& quantity, const string& memo) {
		check(from != to, "cannot transfer to self");
		require_auth(from);
		check(is_account(to), "to account does not exist");
		auto sym = quantity.symbol.code();

		auto newtsym_code = symbol("STVL", 4); // STVL is the token symbol with precision 4
		check(sym == newtsym_code.code(), "This contract can handle NEWT tokens only.");
		stats statstable(get_self(), sym.raw());
		const auto& st = statstable.get(sym.raw());

		require_recipient(from);
		require_recipient(to);

		check(quantity.is_valid(), "invalid quantity");
		check(quantity.amount > 0, "must transfer positive quantity");
		check(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
		check(memo.size() <= 256, "memo has more than 256 bytes");

		auto payer = has_auth(to) ? to : from;

		sub_balance(from, quantity);
		add_balance(to, quantity, payer);
	}


	void token::sub_balance(const name& owner, const asset& value) {
		accounts from_acnts(get_self(), owner.value);

		const auto& from = from_acnts.get(value.symbol.code().raw(), "no balance object found");
		check(from.balance.amount >= value.amount, "overdrawn balance");

		from_acnts.modify(from, owner, [&](auto& a) {
			a.balance -= value;
		});
	}

	void token::add_balance(const name& owner, const asset& value, const name& ram_payer) {
		accounts to_acnts(get_self(), owner.value);
		auto to = to_acnts.find(value.symbol.code().raw());
		if (to == to_acnts.end()) {
			to_acnts.emplace(ram_payer, [&](auto& a) {
				a.balance = value;
			});
		} else {
			to_acnts.modify(to, same_payer, [&](auto& a) {
				a.balance += value;
			});
		}
	}

	void token::open(const name& owner, const symbol& symbol, const name& ram_payer) {
		require_auth(ram_payer);

		check(is_account(owner), "owner account does not exist");

		auto sym_code_raw = symbol.code().raw();
		stats statstable(get_self(), sym_code_raw);
		const auto& st = statstable.get(sym_code_raw, "symbol does not exist");
		check(st.supply.symbol == symbol, "symbol precision mismatch");

		accounts acnts(get_self(), owner.value);
		auto it = acnts.find(sym_code_raw);
		if (it == acnts.end()) {
			acnts.emplace(ram_payer, [&](auto& a) {
				a.balance = asset{ 0, symbol };
			});
		}
	}

	void token::close(const name& owner, const symbol& symbol) {
		require_auth(owner);
		accounts acnts(get_self(), owner.value);
		auto it = acnts.find(symbol.code().raw());
		check(it != acnts.end(), "Balance row already deleted or never existed. Action won't have any effect.");
		check(it->balance.amount == 0, "Cannot close because the balance is not zero.");
		acnts.erase(it);
	}

	void token::airgrab(const name& owner) {
		check(starts_with_vowel(owner.to_string()) == 0, "Account is not qualified, it must start with a vowel.");
		check(_self != owner, "Cannot airgrab from NEWT owner account.");

		require_auth(owner);
		require_recipient(_self); // from
		require_recipient(owner); // to

		auto sym = symbol("STVL", 4); // STVL is the token symbol with precision 4
		asset airgrabbed_asset(1000000, sym);    // allow 100 tokens to be airgrabbed

		// Check if the user have airgrabbed their tokens
		airgrabs airgrab_table(get_self(), sym.raw());

		auto it = airgrab_table.find(owner.value);
		check(it == airgrab_table.end(), "You have already airgrabbed your tokens");

		sub_balance(_self, airgrabbed_asset);
		add_balance(owner, airgrabbed_asset, owner);

		// Register the airgrab so it will not be able to do it the second time
		airgrab_table.emplace(owner, [&](auto& row) {
			row.account = owner;
		});
	}

	int token::starts_with_vowel(string account_name) {
		if (!(account_name[0] == 'A' || account_name[0] == 'a' || account_name[0] == 'E' || account_name[0] == 'e' || account_name[0] == 'I' || account_name[0] == 'i' || account_name[0] == 'O' || account_name[0] == 'o' || account_name[0] == 'U' || account_name[0] == 'u'))
			return 1;
		else
			return 0;
	}

} /// namespace eosio#include <eosiostokveltoken.hpp>
