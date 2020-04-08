open ReactNative;

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "buttonWrapper": style(~width=100.->pct, ~justifyContent=`flexEnd, ()),
      "button":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~backgroundColor="#fff",
          ~borderColor="black",
          ~borderTopWidth=1.,
          ~fontSize=28.,
          ~width=100.->pct,
          ~alignItems=`center,
          (),
        ),
      "txtBlk":
        style(
          ~fontFamily="Montserrat",
          ~color="black",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
      "txtLight":
        style(
          ~fontFamily="Montserrat-Light",
          ~color="black",
          ~fontSize=24.,
          ~lineHeight=48.,
          (),
        ),
    })
  );

[@react.component]
let make = (~submit, ~valid) => {
  <View style={styles##buttonWrapper}>
    <View style={styles##button}>
      <TouchableNativeFeedback
        background={TouchableNativeFeedback.Background.ripple("#000", false)}
        onPress={_ => submit()}>
        <Text
          style={Style.listOption([
            Some(styles##txtBlk),
            valid() ? None : Some(styles##txtLight),
          ])}>
          "CONTINUAR"->React.string
        </Text>
      </TouchableNativeFeedback>
    </View>
  </View>;
};