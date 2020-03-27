/**
 * Do not modify this file - it is a proxy to your `App.re` file
 * located in the `src/` folder.
 */
import 'react-native-gesture-handler';

import React from 'react';
import {StyleSheet} from 'react-native';
import {app as ReasonApp} from './src/App.bs.js';
import {NavigationContainer} from '@react-navigation/native';

export default class App extends React.Component {
  render() {
    return (
      <NavigationContainer>
        <ReasonApp class={styles.container} />
      </NavigationContainer>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
