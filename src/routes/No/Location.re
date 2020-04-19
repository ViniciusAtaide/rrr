let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg":
        style(~backgroundColor="rgb(224, 224, 224)", ~height=100.->pct, ()),
      "container":
        style(~paddingTop=30.->dp, ~paddingBottom=10.->dp, ~flex=1., ()),
      "map": style(~position=`absolute, ~top=(-25.)->dp, ~right=10.->dp, ()),
      "subtitle":
        style(
          ~fontFamily="Montserrat-Bold",
          ~marginLeft=10.->dp,
          ~fontSize=10.,
          (),
        ),
      "title":
        style(
          ~fontFamily="Montserrat-Bold",
          ~marginTop=10.->dp,
          ~marginBottom=20.->dp,
          ~marginLeft=10.->dp,
          ~fontSize=16.,
          ~textTransform=`uppercase,
          (),
        ),
      "titleInverted":
        style(
          ~fontFamily="Montserrat-Bold",
          ~fontSize=16.,
          ~marginLeft=(-12.)->dp,
          ~marginVertical=5.->dp,
          ~textTransform=`uppercase,
          (),
        ),
      "image": style(~width=100.->pct, ~height=250.->dp, ()),
      "number":
        style(
          ~borderColor="rgb(76,76,76)",
          ~borderRadius=5.,
          ~borderWidth=2.,
          ~paddingHorizontal=30.->dp,
          ~paddingVertical=4.->dp,
          ~marginTop=10.->dp,
          ~marginHorizontal=5.->dp,
          (),
        ),
      "center":
        style(~alignItems=`center, ~justifyContent=`center, ~flex=1., ()),
      "horizontal":
        style(
          ~flexDirection=`row,
          ~flexWrap=`wrap,
          ~marginVertical=10.->dp,
          (),
        ),
      "txt": style(~fontFamily="Montserrat", ()),
      "bold": style(~fontFamily="Montserrat-Bold", ()),
      "equal": style(~justifyContent=`flexEnd, ()),
      "email":
        style(
          ~marginTop=(-10.)->dp,
          ~backgroundColor="rgb(128,128,128)",
          ~paddingVertical=5.->dp,
          ~paddingHorizontal=10.->dp,
          ~color="white",
          ~fontSize=10.,
          (),
        ),
      "site":
        style(
          ~backgroundColor="rgb(128,128,128)",
          ~paddingVertical=5.->dp,
          ~paddingHorizontal=10.->dp,
          ~color="white",
          ~fontSize=10.,
          (),
        ),
      "darkBackground":
        style(~backgroundColor="rgb(76,76,76)", ~paddingVertical=30.->dp, ()),
      "txtCenter":
        style(
          ~textAlign=`center,
          ~fontSize=12.,
          ~width=250.->dp,
          ~marginVertical=15.->dp,
          (),
        ),
      "iconSize": style(~height=60.->dp, ~width=60.->dp, ()),
      "iconBottom": style(~width=10.->dp, ()),
      "flex": style(~flex=1., ~alignItems=`center, ()),
    })
  );

[@react.component]
let make =
    (
      ~navigation,
      ~route:
         ReactNavigation.Core.route(
           Navigators.MapNavigator.StakeParams.params,
         ),
    ) => {
  let location = route.params->Belt.Option.map(param => param.location);

  ReactNative.(
    <ScrollView style={styles##bg}>
      <ReactNativeSvg.SvgXml
        style={styles##map}
        xml=Svgs.mapa
        width={130.->Style.dp}
        height={175.->Style.dp}
      />
      <View style={styles##container}>
        <Text style={styles##subtitle}>
          {j|NOSSO ESCRITÓRIO EM|j}->React.string
        </Text>
        {location->Belt.Option.mapWithDefault(
           React.null,
           loc => {
             let email = loc.email->Belt.Option.getWithDefault("");
             let picture =
               loc.name |> Js.String.replaceByRe([%re "/[^A-Z]/g"], "");
             Js.log(picture);
             <>
               <Text style={styles##title}> {React.string(loc.name)} </Text>
               <Text style={styles##titleInverted}>
                 {React.string(loc.name)}
               </Text>
               <ImageBackground
                 style={styles##image}
                 source={Image.Source.fromUriSource(
                   Image.uriSource(
                     ~uri={j|https://mia.adv.br/$picture.jpeg|j},
                     (),
                   ),
                 )}
               />
               <View style={styles##center}>
                 <View
                   style={Style.list([styles##horizontal, styles##center])}>
                   {switch (loc.phonesByPlaceId.nodes) {
                    | [||] => <Text> "Nenhum Telefone"->React.string </Text>
                    | _ =>
                      loc.phonesByPlaceId.nodes
                      ->Belt.Array.map(node => {
                          node->Belt.Option.mapWithDefault(
                            React.null,
                            node => {
                              let ddd =
                                node.number
                                |> Js.String.slice(~from=0, ~to_=2);
                              let number =
                                node.number
                                |> Js.String.slice(~from=2, ~to_=-1);

                              <TouchableOpacity
                                key=number
                                onPress={_ =>
                                  Linking.openURL({j|tel:$ddd$number|j})
                                  |> ignore
                                }>
                                <View style={styles##number}>
                                  <Text style={styles##txt}>
                                    ddd->React.string
                                    <Text style={styles##bold}>
                                      number->React.string
                                    </Text>
                                  </Text>
                                </View>
                              </TouchableOpacity>;
                            },
                          )
                        })
                      ->React.array
                    }}
                 </View>
                 <View
                   style={Style.list([
                     styles##horizontal,
                     styles##darkBackground,
                   ])}>
                   <View style={styles##center}>
                     <TouchableOpacity
                       style=Style.(style(~flex=1., ~alignItems=`center, ()))
                       onPress={_ =>
                         navigation->Navigators.RootNavigator.Navigation.navigate(
                           "Contact",
                         )
                       }>
                       <ReactNativeSvg.SvgXml
                         width={60.->Style.dp}
                         height={70.->Style.dp}
                         xml=Svgs.carta
                       />
                       <Text style={styles##email}>
                         {React.string(email)}
                       </Text>
                     </TouchableOpacity>
                   </View>
                   <View style={styles##center}>
                     <TouchableOpacity
                       style=Style.(style(~flex=1., ~alignItems=`center, ()))
                       onPress={_ =>
                         Linking.openURL("https://www.marcosinacio.adv.br")
                         |> ignore
                       }>
                       <ReactNativeSvg.SvgXml
                         width={60.->Style.dp}
                         height={60.->Style.dp}
                         xml=Svgs.site
                       />
                       <Text style={styles##site}>
                         {React.string("www.marcosinacio.adv.br")}
                       </Text>
                     </TouchableOpacity>
                   </View>
                 </View>
                 <Text style={styles##txtCenter}>
                   {j|Conteúdo jurídico, atendimento online e muito mais em nossas redes sociais:|j}
                   ->React.string
                 </Text>
                 <View
                   style={Style.list([styles##equal, styles##horizontal])}>
                   <View style={styles##flex}>
                     <TouchableOpacity
                       onPress={_ =>
                         Linking.openURL(
                           "https://www.instagram.com/marcosinacio.adv/",
                         )
                         |> ignore
                       }>
                       <ReactNativeSvg.SvgXml
                         width={39.->Style.dp}
                         height={39.->Style.dp}
                         xml=Svgs.insta
                       />
                     </TouchableOpacity>
                   </View>
                   <View style={styles##flex}>
                     <TouchableOpacity
                       onPress={_ =>
                         Linking.openURL(
                           "https://www.facebook.com/MarcosInacioAdvogados/",
                         )
                         |> ignore
                       }>
                       <ReactNativeSvg.SvgXml
                         width={26.->Style.dp}
                         height={48.->Style.dp}
                         xml=Svgs.face
                       />
                     </TouchableOpacity>
                   </View>
                   <View style={styles##flex}>
                     <TouchableOpacity
                       onPress={_ =>
                         Linking.openURL(
                           "https://www.linkedin.com/company/marcos-in%C3%A1cio-advogados/",
                         )
                         |> ignore
                       }>
                       <ReactNativeSvg.SvgXml
                         width={25.->Style.dp}
                         height={27.->Style.dp}
                         xml=Svgs.linked
                       />
                     </TouchableOpacity>
                   </View>
                   <View style={styles##flex}>
                     <TouchableOpacity
                       style=Style.(style(~flex=1., ~alignItems=`center, ()))
                       onPress={_ =>
                         Linking.openURL("https://twitter.com/miadvocacia")
                         |> ignore
                       }>
                       <ReactNativeSvg.SvgXml
                         width={49.->Style.dp}
                         height={39.->Style.dp}
                         xml=Svgs.twitter
                       />
                     </TouchableOpacity>
                   </View>
                   <View style={styles##flex}>
                     <TouchableOpacity
                       style=Style.(style(~flex=1., ~alignItems=`center, ()))
                       onPress={_ =>
                         Linking.openURL("https://bit.ly/2Fcl1mI") |> ignore
                       }>
                       <ReactNativeSvg.SvgXml
                         width={48.->Style.dp}
                         height={34.->Style.dp}
                         xml=Svgs.tube
                       />
                     </TouchableOpacity>
                   </View>
                 </View>
               </View>
             </>;
           },
         )}
      </View>
    </ScrollView>
  );
};