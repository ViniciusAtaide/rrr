open ReactNavigation;

let styles =
  ReactNative.(
    Style.{
      "header":
        style(
          ~backgroundColor="rgb(36, 36, 36)",
          ~shadowColor="transparent",
          (),
        ),
      "title": style(~color="white", ()),
    }
    ->StyleSheet.create
  );

module MainStackScreen = {
  let rootOptions = _ =>
    ReactNative.Platform.(
      Navigators.RootNavigator.options(
        ~headerShown=os === ios,
        ~headerStyle=styles##header,
        ~title="",
        ~headerTintColor="white",
        ~headerTransparent=true,
        ~headerBackTitleVisible=false,
        (),
      )
    );
  // open ReactNative;
  [@react.component]
  let make = (~navigation as _, ~route as _) =>
    <Navigators.RootNavigator.Navigator mode=`card>
      <Navigators.RootNavigator.Screen
        name="Welcome"
        component=Welcome.make
        options={_ =>
          Navigators.RootNavigator.options(
            ~headerShown=false,
            ~headerStyle=styles##header,
            (),
          )
        }
      />
      <Navigators.RootNavigator.Screen
        name="Guest"
        component=Guest.make
        options=rootOptions
      />
      <Navigators.RootNavigator.Screen
        name="Contact"
        component=Contact.make
        options=rootOptions
      />
      <Navigators.RootNavigator.Screen
        name="Speak"
        component=Speak.make
        options=rootOptions
      />
      <Navigators.RootNavigator.Screen
        name="Media"
        component=Media.make
        options=rootOptions
      />
    </Navigators.RootNavigator.Navigator>;
};
module SubscribeStackScreen = {
  include Navigators.SubscribeNavigator;
  let subscribeOptions = _ =>
    ReactNative.Platform.(
      Navigators.SubscribeNavigator.options(
        ~headerShown=os === ios,
        ~headerStyle=styles##header,
        ~title="",
        ~headerTransparent=true,
        ~headerTintColor="white",
        ~headerBackTitleVisible=false,
        (),
      )
    );

  [@react.component]
  let make = (~navigation as _, ~route as _) => {
    <Navigators.SubscribeNavigator.Navigator
      mode=`card initialRouteName="Credentials">
      <Navigators.SubscribeNavigator.Screen
        name="Credentials"
        component=Credentials.make
        options={_ =>
          ReactNative.Platform.(
            Navigators.SubscribeNavigator.options(
              ~headerShown=os === ios,
              ~headerStyle=styles##header,
              ~title="",
              ~headerTransparent=true,
              ~headerTintColor="white",
              (),
            )
          )
        }
      />
      <Navigators.SubscribeNavigator.Screen
        name="Subscribe"
        component=Subscribe.make
        options=subscribeOptions
      />
      <Navigators.SubscribeNavigator.Screen
        name="Options"
        component=Options.make
        options=subscribeOptions
      />
    </Navigators.SubscribeNavigator.Navigator>;
  };
};

module MapStackScreen = {
  include Navigators.MapNavigator;
  let mapOptions = _ =>
    ReactNative.Platform.(
      Navigators.MapNavigator.options(
        ~headerShown=os === ios,
        ~title="",
        ~headerTransparent=true,
        ~headerBackTitleVisible=false,
        (),
      )
    );

  [@react.component]
  let make = (~navigation as _, ~route as _) => {
    <Navigators.MapNavigator.Navigator mode=`card initialRouteName="Init">
      <Navigators.MapNavigator.Screen
        name="Init"
        component=Map.make
        options={_ =>
          ReactNative.Platform.(
            Navigators.MapNavigator.options(
              ~headerShown=os === ios,
              ~title="",
              ~headerTransparent=true,
              ~headerBackTitleVisible=false,
              (),
            )
          )
        }
      />
      <Navigators.MapNavigator.Screen
        name="Location"
        component=Location.make
        options=mapOptions
      />
    </Navigators.MapNavigator.Navigator>;
  };
};

module RootStackScreen = {
  open ReactNative.Platform;

  include Stack.Make({
    type params = unit;
  });

  [@react.component]
  let make = () => {
    <Navigator mode=`card initialRouteName="Main">
      <Screen
        name="Main"
        component=MainStackScreen.make
        options={_ => options(~headerShown=false, ())}
      />
      <Screen
        name="Auth"
        component=SubscribeStackScreen.make
        options={_ =>
          options(
            ~headerShown=os === ios,
            ~title="",
            ~headerTransparent=true,
            ~headerTintColor="white",
            ~headerBackTitleVisible=false,
            (),
          )
        }
      />
      <Screen
        name="Map"
        component=MapStackScreen.make
        options={_ =>
          options(
            ~headerShown=os === ios,
            ~title="",
            ~headerTransparent=true,
            ~headerTintColor="white",
            ~headerBackTitleVisible=false,
            (),
          )
        }
      />
    </Navigator>;
  };
};