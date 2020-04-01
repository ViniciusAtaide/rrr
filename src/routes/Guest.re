let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~height=100.->pct,
          ~padding=25.->dp,
          (),
        ),
      "txt":
        style(
          ~color="#fff",
          ~fontSize=28.,
          ~paddingTop=20.->dp,
          ~fontWeight=`_600,
          (),
        ),
      "orange":
        style(~color="rgb(223,63,42)", ~fontWeight=`_700, ~fontSize=28., ()),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  ReactNative.(
    <View style={styles##bg}>
      <View style={styles##container}>
        <Text style={styles##orange}>
          {js|O que deseja?!|js}->React.string
        </Text>
        <TouchableOpacity
          onPress={_ =>
            navigation->RootNavigator.Navigation.navigate("Speak")
          }>
          <Text style={styles##txt}>
            "Falar com um atendente"->React.string
          </Text>
        </TouchableOpacity>
        <TouchableOpacity>
          <Text style={styles##txt}>
            {js|Encontrar o escritório mais perto de você|js}->React.string
          </Text>
        </TouchableOpacity>
        <TouchableOpacity
          onPress={_ =>
            navigation->RootNavigator.Navigation.navigate("Contact")
          }>
          <Text style={styles##txt}>
            {js|Fazer elogios ou reclamações|js}->React.string
          </Text>
        </TouchableOpacity>
      </View>
    </View>
  );
};