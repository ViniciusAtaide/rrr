open ReactNavigation;

module RootNavigator = {
  include Stack.Make({
    type params = unit;
  });
};

module MapNavigator = {
  module StakeParams = {
    type params = {location: MapQuery_graphql.Types.allPlaces_nodes};
  };
  include Stack.Make(StakeParams);
};

module SubscribeNavigator = {
  module StakeParams = {
    type params = {cpfCnpj: string};
  };
  include Stack.Make(StakeParams);
};