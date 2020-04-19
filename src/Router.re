open ReactNavigation;

module MainStackScreen = {
  [@react.component]
  let make = (~navigation as _, ~route as _) =>
    <Navigators.RootNavigator.Navigator mode=`card headerMode=`none>
      <Navigators.RootNavigator.Screen name="Welcome" component=Welcome.make />
      <Navigators.RootNavigator.Screen name="Guest" component=Guest.make />
      <Navigators.RootNavigator.Screen name="Contact" component=Contact.make />
      <Navigators.RootNavigator.Screen name="Speak" component=Speak.make />
      <Navigators.RootNavigator.Screen name="Media" component=Media.make />
      <Navigators.RootNavigator.Screen name="Options" component=Options.make />
    </Navigators.RootNavigator.Navigator>;
};

module SubscribeStackScreen = {
  include Navigators.SubscribeNavigator;

  [@react.component]
  let make = (~navigation as _, ~route as _) => {
    <Navigators.SubscribeNavigator.Navigator
      mode=`card headerMode=`none initialRouteName="Credentials">
      <Navigators.RootNavigator.Screen
        name="Credentials"
        component=Credentials.make
      />
      <Navigators.SubscribeNavigator.Screen
        name="Subscribe"
        component=Subscribe.make
      />
    </Navigators.SubscribeNavigator.Navigator>;
  };
};

module MapStackScreen = {
  include Navigators.MapNavigator;

  [@react.component]
  let make = (~navigation as _, ~route as _) => {
    <Navigators.MapNavigator.Navigator
      mode=`card headerMode=`none initialRouteName="Init">
      <Navigators.MapNavigator.Screen name="Init" component=Map.make />
      <Navigators.MapNavigator.Screen
        name="Location"
        component=Location.make
      />
    </Navigators.MapNavigator.Navigator>;
  };
};

module RootStackScreen = {
  include Stack.Make({
    type params = unit;
  });

  [@react.component]
  let make = () => {
    <Navigator mode=`card headerMode=`none initialRouteName="Main">
      <Screen name="Main" component=MainStackScreen.make />
      <Screen name="Auth" component=SubscribeStackScreen.make />
      <Screen name="Map" component=MapStackScreen.make />
    </Navigator>;
  };
};