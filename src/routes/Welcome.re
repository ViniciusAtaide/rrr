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
      "txt": style(~color="#fff", ~fontSize=26., ()),
      "txtSmall": style(~color="#fff", ~fontSize=20., ~fontWeight=`_700, ()),
      "txtBold":
        style(
          ~color="#fff",
          ~fontSize=30.,
          ~fontWeight=`bold,
          ~paddingBottom=30.->dp,
          (),
        ),
      "orange": style(~color="rgb(223,63,42)", ~fontSize=27., ()),
      "orangeButton":
        style(
          ~backgroundColor="rgb(223,63,42)",
          ~width=70.->dp,
          ~height=70.->dp,
          ~borderRadius=100.,
          (),
        ),
      "grayButton":
        style(
          ~backgroundColor="rgb(26,26,25)",
          ~width=70.->dp,
          ~height=70.->dp,
          ~borderRadius=100.,
          ~marginTop=60.->dp,
          (),
        ),
      "buttonText":
        style(
          ~textAlign=`center,
          ~lineHeight=70.,
          ~fontWeight=`_700,
          ~color="#fff",
          ~fontSize=24.,
          (),
        ),
      "horizontal":
        style(
          ~flexDirection=`row,
          ~width=100.->pct,
          ~justifyContent=`spaceBetween,
          ~paddingLeft=50.->pct,
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  ReactNative.(
    <View style={styles##bg}>
      <View style={styles##container}>
        <Text style={styles##txt}> {js|Olá!|js}->React.string </Text>
        <Text style={styles##txt}> "Bem-vindo ao "->React.string </Text>
        <Text style={styles##txt}>
          <Text style={styles##orange}>
            {js|ESCRITÓRIO DIGITAL|js}->ReasonReact.string
          </Text>
          " da "->React.string
        </Text>
        <Text style={styles##txtBold}>
          {js|Marcos Inácio Advogados|js}->React.string
        </Text>
        <Text style={styles##txtSmall}>
          {js|Já é nosso Cliente?|js}->React.string
        </Text>
        <View style={styles##horizontal}>
          <TouchableNativeFeedback
            background={TouchableNativeFeedback.Background.ripple(
              "#fff",
              true,
            )}
            onPress={_ =>
              navigation->RootNavigator.Navigation.navigate("Guest")
            }>
            <View style={styles##grayButton}>
              <Text style={styles##buttonText}>
                {js|NÃO|js}->React.string
              </Text>
            </View>
          </TouchableNativeFeedback>
          <TouchableNativeFeedback
            background={TouchableNativeFeedback.Background.ripple(
              "#fff",
              true,
            )}
            onPress={_ =>
              navigation->RootNavigator.Navigation.navigate("Home")
            }>
            <View style={styles##orangeButton}>
              <Text style={styles##buttonText}> "SIM"->React.string </Text>
            </View>
          </TouchableNativeFeedback>
        </View>
      </View>
    </View>
  );
};