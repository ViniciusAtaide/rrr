open ReactNative;
open Belt;

let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "buttonWrapper":
        style(~flex=1., ~width=100.->pct, ~justifyContent=`flexEnd, ()),
      "button":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~backgroundColor="#fff",
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
let make = (~errors, ~submit=?) => {
  // let environment = ReasonRelay.useEnvironmentFromContext();
  <View style={styles##buttonWrapper}>
    <View style={styles##button}>
      <TouchableNativeFeedback
        background={TouchableNativeFeedback.Background.ripple("#000", false)}
        onPress={_ =>
          errors->Set.String.isEmpty
            ? submit |> ignore
            : ToastAndroid.(
                showWithGravityAndOffset(
                  {j|CPF/CNPJ Obrigatórios|j},
                  long,
                  bottom,
                  ~xOffset=25.,
                  ~yOffset=50.,
                )
              )
        }>
        <Text
          style={Style.listOption([
            errors->Set.String.isEmpty
              ? Some(styles##txtBlk) : Some(styles##txtLight),
          ])}>
          "CONTINUAR"->React.string
        </Text>
      </TouchableNativeFeedback>
    </View>
  </View>;
};