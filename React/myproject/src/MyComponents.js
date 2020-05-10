import React, { Component } from 'react';
import PropTypes from 'prop-types';

/*
import React from "react";

const MyComponent = ({name, children, favoriteNumber}) => {
  //const { name, children } = props2;
  return (
    <div>
      안녕, 내 이름은 {name} 입니다.
      <br />
      children 값은. {children}
      입니다.
      <br />
      제가 좋아하는 숫자는 {favoriteNumber}입니다.
    </div>
  );
};
*/

class MyComponent extends Component {
    render() {
        const {name, favoriteNumber, children} = this.props; 
        return (
            <div>
            안녕, 내 이름은 {name} 입니다.
            <br />
            children 값은. {children}
            입니다.
            <br />
            제가 좋아하는 숫자는 {favoriteNumber}입니다.
          </div>
        );
    }
}


MyComponent.defaultProps = {
  name: "기본 이름2",
};

MyComponent.propTypes = {
    name: PropTypes.string,
    favoriteNumber: PropTypes.number.isRequired
};

export default MyComponent;
