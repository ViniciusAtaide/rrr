let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "imgBg":
        style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~padding=20.->dp,
          ~flex=1.,
          (),
        ),
      "txt":
        style(
          ~color="#fff",
          ~fontSize=26.,
          ~fontFamily="Montserrat-Regular",
          (),
        ),
      "txtSmall":
        style(
          ~color="#fff",
          ~fontSize=20.,
          ~fontFamily="Montserrat-Bold",
          (),
        ),
      "txtBold":
        style(
          ~fontFamily="Montserrat-Bold",
          ~color="#fff",
          ~fontSize=30.,
          ~paddingBottom=30.->dp,
          (),
        ),
      "orange": style(~color="rgb(254,80,0)", ~fontSize=26., ()),
      "orangeButton":
        style(
          ~backgroundColor="rgb(254,80,0)",
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
          (),
        ),
      "half": style(~marginLeft=(-35.)->dp, ()),
      "halfVertical": style(~marginBottom=(-35.)->dp, ()),
      "buttonText":
        style(
          ~textAlign=`center,
          ~lineHeight=70.,
          ~fontFamily="Montserrat-Bold",
          ~color="#fff",
          ~fontSize=22.,
          (),
        ),
      "horizontal":
        style(
          ~flexDirection=`row,
          ~width=100.->pct,
          ~justifyContent=`spaceBetween,
          (),
        ),
      "padding": style(~marginTop=60.->dp, ()),
      "vertical":
        style(
          ~paddingRight=20.->dp,
          ~flexDirection=`column,
          ~justifyContent=`spaceBetween,
          ~flex=1.,
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  ReactNative.(
    <View style={styles##imgBg}>
      <View style={styles##container}>
        <Text style={styles##txt}> {j|Olá!|j}->React.string </Text>
        <Text style={styles##txt}> "Bem-vindo ao "->React.string </Text>
        <Text style={styles##txt}>
          <Text style={styles##orange}>
            {j|ESCRITÓRIO DIGITAL|j}->ReasonReact.string
          </Text>
          " da "->React.string
        </Text>
        <Text style={styles##txtBold}>
          {j|Marcos Inácio Advogados|j}->React.string
        </Text>
        <Text style={styles##txtSmall}>
          {j|Já é nosso Cliente?|j}->React.string
        </Text>
      </View>
      <View style={styles##vertical}>
        <View style={styles##horizontal}>
          <View
            style={Style.list([
              styles##grayButton,
              styles##padding,
              styles##half,
            ])}
          />
          <View style={Style.list([styles##grayButton, styles##padding])} />
          <TouchableHighlight
            onPress={_ =>
              navigation->Navigators.RootNavigator.Navigation.navigate(
                "Guest",
              )
            }>
            <View style={Style.list([styles##grayButton, styles##padding])}>
              <Text style={styles##buttonText}>
                {j|NÃO|j}->React.string
              </Text>
            </View>
          </TouchableHighlight>
          <TouchableHighlight
            onPress={_ =>
              navigation->Navigators.RootNavigator.Navigation.navigate("Auth")
            }>
            <View style={styles##orangeButton}>
              <Text style={styles##buttonText}> "SIM"->React.string </Text>
            </View>
          </TouchableHighlight>
        </View>
        <View style={styles##horizontal}>
          <View style={Style.list([styles##grayButton, styles##half])} />
          <View style={styles##grayButton} />
          <View style={styles##grayButton} />
          <View style={styles##grayButton} />
        </View>
        <View style={Style.list([styles##horizontal, styles##halfVertical])}>
          <View style={Style.list([styles##grayButton, styles##half])} />
          <View style={styles##grayButton} />
          <View style={styles##grayButton} />
          <View style={styles##grayButton} />
        </View>
      </View>
    </View>
  );
};