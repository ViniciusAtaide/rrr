open ReactNavigation;

module MainStackScreen = {
  [@react.component]
  let make = (~navigation as _, ~route as _) =>
    <Navigators.RootNavigator.Navigator mode=`card headerMode=`none>
      <Navigators.RootNavigator.Screen name="Welcome" component=Welcome.make />
      <Navigators.RootNavigator.Screen name="Guest" component=Guest.make />
      <Navigators.RootNavigator.Screen name="Speak" component=Speak.make />
      <Navigators.RootNavigator.Screen name="Contact" component=Contact.make />
      <Navigators.RootNavigator.Screen name="Media" component=Media.make />
      <Navigators.RootNavigator.Screen
        name="Credentials"
        component=Credentials.make
      />
      <Navigators.RootNavigator.Screen name="Options" component=Options.make />
    </Navigators.RootNavigator.Navigator>;
};

module SubscribeStackScreen = {
  [@react.component]
  let make = (~navigation as _, ~route as _) => {
    <Navigators.SubscribeNavigator.Navigator
      mode=`card headerMode=`none initialRouteName="Subscribe">
      <Navigators.SubscribeNavigator.Screen
        name="Subscribe"
        component=Subscribe.make
      />
    </Navigators.SubscribeNavigator.Navigator>;
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
    </Navigator>;
  };
};