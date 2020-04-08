let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~flex=1.,
          ~paddingHorizontal=35.->dp,
          (),
        ),
      "txt":
        style(
          ~fontFamily="Montserrat-SemiBold",
          ~color="#fff",
          ~fontSize=24.,
          ~paddingTop=20.->dp,
          (),
        ),
      "icons":
        style(
          ~flex=1.,
          ~paddingHorizontal=35.->dp,
          ~flexDirection=`column,
          (),
        ),
      "line":
        style(
          ~flexDirection=`row,
          ~width=100.->pct,
          ~justifyContent=`spaceBetween,
          ~marginBottom=40.->dp,
          ~height=65.->dp,
          (),
        ),
      "iconSize": style(~height=65.->dp, ~width=65.->dp, ()),
    })
  );

[@react.component]
let make = (~navigation as _, ~route as _) => {
  ReactNative.Image.Source.(
    ReactNative.(
      <View style={styles##bg}>
        <View style={styles##container}>
          <Text style={styles##txt}>
            {j|Muito obrigado por sua opinião. Buscamos sempre a excelência em nosso serviço.|j}
            ->React.string
          </Text>
          <Text style={styles##txt}>
            {j|Conteúdo jurídico:|j}->React.string
          </Text>
        </View>
        <View style={styles##icons}>
          <View style={styles##line}>
            <TouchableNativeFeedback
              onPress={_ =>
                Linking.openURL("https://www.instagram.com/marcosinacio.adv/")
                |> ignore
              }>
              <Image
                style={Style.list([styles##iconSize])}
                source={fromRequired(
                  Packager.require("./Media/Insta-01.png"),
                )}
              />
            </TouchableNativeFeedback>
            <TouchableNativeFeedback
              onPress={_ =>
                Linking.openURL(
                  "https://www.facebook.com/MarcosInacioAdvogados/",
                )
                |> ignore
              }>
              <Image
                style={Style.list([styles##iconSize])}
                source={fromRequired(
                  Packager.require("./Media/Face-01.png"),
                )}
              />
            </TouchableNativeFeedback>
            <TouchableNativeFeedback
              onPress={_ =>
                Linking.openURL("https://www.marcosinacio.adv.br/") |> ignore
              }>
              <Image
                style={Style.list([styles##iconSize])}
                source={fromRequired(Packager.require("./Media/Site.png"))}
              />
            </TouchableNativeFeedback>
          </View>
          <View style={styles##line}>
            <TouchableNativeFeedback
              onPress={_ =>
                Linking.openURL(
                  "https://www.linkedin.com/company/marcos-in%C3%A1cio-advogados/",
                )
                |> ignore
              }>
              <Image
                style={Style.list([styles##iconSize])}
                source={fromRequired(
                  Packager.require("./Media/Linked-01.png"),
                )}
              />
            </TouchableNativeFeedback>
            <TouchableNativeFeedback
              onPress={_ =>
                Linking.openURL("https://bit.ly/2Fcl1mI") |> ignore
              }>
              <Image
                style={Style.list([styles##iconSize])}
                source={fromRequired(
                  Packager.require("./Media/Tube-01.png"),
                )}
              />
            </TouchableNativeFeedback>
            <TouchableNativeFeedback
              onPress={_ =>
                Linking.openURL("https://twitter.com/miadvocacia") |> ignore
              }>
              <Image
                style={Style.list([styles##iconSize])}
                source={fromRequired(
                  Packager.require("./Media/Twitter-01.png"),
                )}
              />
            </TouchableNativeFeedback>
          </View>
        </View>
      </View>
    )
  );
};