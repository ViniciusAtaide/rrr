let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`spaceBetween,
          ~paddingHorizontal=25.->dp,
          ~paddingVertical=60.->dp,
          ~flex=1.,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#fff",
          ~fontSize=24.,
          ~marginVertical=10.->pct,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~paddingTop=40.->dp,
          ~fontFamily="Montserrat-Bold",
          ~fontSize=22.,
          (),
        ),
      "center":
        style(
          ~justifyContent=`spaceAround,
          ~alignItems=`center,
          ~width=100.->pct,
          (),
        ),
      "signature": style(~width=150.->dp, ~height=90.->dp, ()),
      "figure": style(~width=150.->dp, ~height=50.->dp, ()),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  ReactNative.(
    <View style={styles##bg}>
      <View style={styles##container}>
        <Text style={styles##orange}>
          {j|O que deseja?!|j}->React.string
        </Text>
        <View>
          <TouchableOpacity
            onPress={_ =>
              navigation->Navigators.RootNavigator.Navigation.navigate(
                "Speak",
              )
            }>
            <Text style={styles##txt}>
              {j|Falar com um atendente|j}->React.string
            </Text>
          </TouchableOpacity>
          <TouchableOpacity
            onPress={_ =>
              navigation->Navigators.MapNavigator.Navigation.navigate("Map")
            }>
            <Text style={styles##txt}>
              {j|Encontrar o escritório mais perto de você|j}->React.string
            </Text>
          </TouchableOpacity>
          <TouchableOpacity
            onPress={_ =>
              navigation->Navigators.RootNavigator.Navigation.navigate(
                "Contact",
              )
            }>
            <Text style={styles##txt}>
              {j|Fazer elogios ou reclamações|j}->React.string
            </Text>
          </TouchableOpacity>
        </View>
        <View style={styles##center}>
          <Image
            source={Image.Source.fromRequired(
              Packager.require("../../images/signature.png"),
            )}
            style={styles##signature}
          />
          <Image
            source={Image.Source.fromRequired(
              Packager.require("../../images/30years.png"),
            )}
            style={styles##figure}
          />
        </View>
      </View>
    </View>
  );
};