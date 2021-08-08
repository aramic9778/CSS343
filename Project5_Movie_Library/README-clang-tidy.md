The only clang-tidy warnings we were not ablt to fix were the ones that are listed bellow.
This warnings appere because we create this objects for registering the type at runtime.


/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/borrowCommand.cpp:73:22: error: initialization of 'anonymousBorrowCommandFactory' with static storage duration may throw an exception that cannot be caught [cert-err58-cpp,-warnings-as-errors]
BorrowCommandFactory anonymousBorrowCommandFactory;
                     ^
/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/borrowCommand.h:58:3: note: possibly throwing constructor declared here
  BorrowCommandFactory() { Command::registerType('B', this); }
  ^

/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/classics.cpp:60:17: error: initialization of 'anonymousClassicsFactory' with static storage duration may throw an exception that cannot be caught [cert-err58-cpp,-warnings-as-errors]
ClassicsFactory anonymousClassicsFactory;
                ^
/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/classics.h:58:3: note: possibly throwing constructor declared here
  ClassicsFactory() { Movie::registerType('C', this); }
  ^

/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/comedy.cpp:50:15: error: initialization of 'anonymousComedyFactory' with static storage duration may throw an exception that cannot be caught [cert-err58-cpp,-warnings-as-errors]
ComedyFactory anonymousComedyFactory;
              ^
/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/comedy.h:49:3: note: possibly throwing constructor declared here
  ComedyFactory() { Movie::registerType('F', this); }
  ^

/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/drama.cpp:51:14: error: initialization of 'anonymousDramaFactory' with static storage duration may throw an exception that cannot be caught [cert-err58-cpp,-warnings-as-errors]
DramaFactory anonymousDramaFactory;
             ^
/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/drama.h:48:3: note: possibly throwing constructor declared here
  DramaFactory() { Movie::registerType('D', this); }
  ^

/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/historyCommand.cpp:36:23: error: initialization of 'anonymousHistoryCommandFactory' with static storage duration may throw an exception that cannot be caught [cert-err58-cpp,-warnings-as-errors]
HistoryCommandFactory anonymousHistoryCommandFactory;
                      ^
/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/historyCommand.h:49:3: note: possibly throwing constructor declared here
  HistoryCommandFactory() { Command::registerType('H', this); }
  ^

/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/inventoryCommand.cpp:31:25: error: initialization of 'anonymousInventoryCommandFactory' with static storage duration may throw an exception that cannot be caught [cert-err58-cpp,-warnings-as-errors]
InventoryCommandFactory anonymousInventoryCommandFactory;
                        ^
/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/inventoryCommand.h:50:3: note: possibly throwing constructor declared here
  InventoryCommandFactory() { Command::registerType('I', this); }
  ^

/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/returnCommand.cpp:74:22: error: initialization of 'anonymousReturnCommandFactory' with static storage duration may throw an exception that cannot be caught [cert-err58-cpp,-warnings-as-errors]
ReturnCommandFactory anonymousReturnCommandFactory;
                     ^
/home/NETID/olhak/2021wi343b-movie-olga-kuriatnyk/returnCommand.h:55:3: note: possibly throwing constructor declared here
  ReturnCommandFactory() { Command::registerType('R', this); }
  ^