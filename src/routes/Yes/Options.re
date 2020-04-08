let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ()),
      "top": style(~paddingHorizontal=12.5->dp, ()),
      "container":
        style(
          ~justifyContent=`flexStart,
          ~height=100.->pct,
          ~paddingTop=10.->dp,
          ~paddingHorizontal=12.5->dp,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#000",
          ~fontSize=16.,
          ~textAlign=`center,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~fontFamily="Montserrat-SemiBold",
          ~fontSize=26.,
          ~width=200.->dp,
          ~marginBottom=40.->dp,
          (),
        ),
      "horizontal":
        style(
          ~flexWrap=`wrap,
          ~flexDirection=`row,
          ~justifyContent=`spaceBetween,
          (),
        ),
      "button":
        style(
          ~backgroundColor="rgb(144,144,144)",
          ~justifyContent=`center,
          ~padding=5.->dp,
          ~marginVertical=12.5->dp,
          ~marginHorizontal=12.5->dp,
          ~flexGrow=1.,
          ~height=140.->dp,
          ~flexBasis=42.->pct,
          (),
        ),
      "signature": style(~width=100.->dp, ~height=70.->dp, ()),
      "dna":
        style(
          ~position=`absolute,
          ~height=100.->pct,
          ~width=100.->pct,
          ~right=0.->dp,
          ~zIndex=-1,
          ~resizeMode=`repeat,
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation, ~route as _) => {
  ReactNative.(
    <View style={styles##bg}>
      <View style={styles##container}>
        <ImageBackground
          style={styles##dna}
          source={Image.Source.fromRequired(
            Packager.require("./Options/dna.png"),
          )}
        />
        <View style={styles##top}>
          <Image
            style={styles##signature}
            source={Image.Source.fromRequired(
              Packager.require("../../images/signature.png"),
            )}
          />
          <Text style={styles##orange}>
            {j|ESCRITÓRIO DIGITAL.|j}->React.string
          </Text>
        </View>
        <View style={styles##horizontal}>
          <TouchableNativeFeedback
            onPress={_ =>
              Linking.openURL(
                "https://www.marcosinacio.adv.br/inteligencia-juridica",
              )
              |> ignore
            }>
            <View style={styles##button}>
              <Text style={styles##txt}>
                {j|CONTEÚDO JURÍDICO|j}->React.string
              </Text>
            </View>
          </TouchableNativeFeedback>
          <TouchableNativeFeedback>
            <View style={styles##button}>
              <Text style={styles##txt}>
                {j|Falar com advogado|j}->React.string
              </Text>
            </View>
          </TouchableNativeFeedback>
          <TouchableNativeFeedback>
            <View style={styles##button}>
              <Text style={styles##txt}>
                {j|Consultar meu processo|j}->React.string
              </Text>
            </View>
          </TouchableNativeFeedback>
          <TouchableNativeFeedback>
            <View style={styles##button}>
              <Text style={styles##txt}>
                {j|Falar com atendente|j}->React.string
              </Text>
            </View>
          </TouchableNativeFeedback>
          <TouchableNativeFeedback>
            <View style={styles##button}>
              <Text style={styles##txt}>
                {j|Meu amigo precisa de um advogado|j}->React.string
              </Text>
            </View>
          </TouchableNativeFeedback>
          <TouchableNativeFeedback
            onPress={_ =>
              navigation->Navigators.RootNavigator.Navigation.navigate(
                "Contact",
              )
            }>
            <View style={styles##button}>
              <Text style={styles##txt}>
                {j|Elogios e críticas|j}->React.string
              </Text>
            </View>
          </TouchableNativeFeedback>
        </View>
      </View>
    </View>
  );
};