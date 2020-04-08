open ReactNavigation;

module RootNavigator = {
  include Stack.Make({
    type params = unit;
  });
};

module SubscribeNavigator = {
  module StakeParams = {
    type params = {cpfCnpj: string};
  };
  include Stack.Make(StakeParams);
};