Never use top-level const on function parameters in declarations that are not definitions (and be careful not to copy/paste a meaningless const). It is meaningless and ignored by the compiler, it is visual noise, and it could mislead readers.


Do use top-level const on function parameters in definitions at your (or your team’s) discretion. You might follow the same rationale as you would for when to declare a function-local variable const.