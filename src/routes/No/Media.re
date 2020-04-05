let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~flex=1.,
          ~padding=25.->dp,
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
      "icons": style(~flex=1., ~flexDirection=`column, ()),
      "line": style(~flexDirection=`row, ~height=50.->dp, ()),
      "iconSize": style(~height=120.->dp, ~width=120.->dp, ()),
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
            <Image
              style={Style.list([styles##iconSize])}
              source={fromRequired(Packager.require("./Media/Insta-01.png"))}
            />
            <Image
              style={Style.list([styles##iconSize])}
              source={fromRequired(Packager.require("./Media/Face-01.png"))}
            />
            <Image
              style={Style.list([styles##iconSize])}
              source={fromRequired(Packager.require("./Media/Site.png"))}
            />
          </View>
          <View style={styles##line}>
            <Image
              style={Style.list([styles##iconSize])}
              source={fromRequired(
                Packager.require("./Media/Linked-01.png"),
              )}
            />
            <Image
              style={Style.list([styles##iconSize])}
              source={fromRequired(Packager.require("./Media/Tube-01.png"))}
            />
            <Image
              style={Style.list([styles##iconSize])}
              source={fromRequired(
                Packager.require("./Media/Twitter-01.png"),
              )}
            />
          </View>
        </View>
      </View>
    )
  );
};