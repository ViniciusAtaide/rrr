open RootNavigator;

[@react.component]
let make = () =>
  <Navigator mode=`card headerMode=`none initialRouteName="Welcome">
    <Screen name="Welcome" component=Welcome.make />
    <Screen name="Guest" component=Guest.make />
    <Screen name="Speak" component=Speak.make />
    <Screen name="Contact" component=Contact.make />
    <Screen name="Home" component=Home.make />
  </Navigator>;