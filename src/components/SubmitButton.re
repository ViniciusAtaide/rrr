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
let make = (~submit, ~valid, ~loading) => {
  <View style={styles##buttonWrapper}>
    <TouchableNativeFeedback
      background={TouchableNativeFeedback.Background.ripple("#000", false)}
      onPress={_ => loading ? () : submit()}>
      <View style={styles##button}>
        <Text
          style={Style.listOption([
            Some(styles##txtBlk),
            valid() ? None : Some(styles##txtLight),
          ])}>
          {loading
             ? <Image
                 source={Image.Source.fromRequired(
                   Packager.require("../images/loading.gif"),
                 )}
               />
             : "CONTINUAR"->React.string}
        </Text>
      </View>
    </TouchableNativeFeedback>
  </View>;
};