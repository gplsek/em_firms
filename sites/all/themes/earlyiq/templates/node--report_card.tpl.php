<?php

  // Default Values
  $company_name = "[Company Name]";
  $company_description = "[Company Description]";
  $company_address = "[Company Address]";
  $company_phone = "[Company Phone]";	
  $company_url = "http://www.companyurl.com";
  $officers = array();
  
  
  $companyNodeID = $node->field_company["und"][0]["nid"];
  
  if(!empty($companyNodeID)) {
  
    $companyNode = node_load($companyNodeID, null, true);
    
    if(!empty($companyNode)) {
          
      try {
        $company_name = $companyNode->title;
        $company_description = $companyNode->body["und"][0]["safe_value"];
        $company_url = $companyNode->field_website["und"][0]["url"];
        $company_phone = $companyNode->field_company_phone["und"][0]["value"];
        
        // Get Address
        $companyAddressNodeID = $companyNode->field_company_address["und"][0]["value"];
        
        $companyAddressNode = entity_load('field_collection_item', array($companyAddressNodeID));
        $companyAddressNode = reset($companyAddressNode); // get first element in the array
        
        $company_address1 = $companyAddressNode->field_address_address1["und"][0]["safe_value"];
        $company_address2 = $companyAddressNode->field_address_address2["und"][0]["safe_value"];
        $company_address_city = $companyAddressNode->field_address_city["und"][0]["safe_value"];
        $company_address_state = $companyAddressNode->field_address_state["und"][0]["value"];
        $company_address_zipcode = $companyAddressNode->field_address_zip["und"][0]["postal"];
        
        $company_address = $company_address1."<br/>";
        if(!empty($company_address2)) {
          $company_address .= $company_address2."<br/>";          
        }
        $company_address .= $company_address_city.",&nbsp;".
                            $company_address_state."&nbsp;".
                            $company_address_zipcode;
        
        // Get Officers
        $companyOfficersNodeID = $companyNode->field_invite_officers["und"][0]["value"];
        $companyOfficersNode = entity_load('field_collection_item', array($companyOfficersNodeID));

        foreach($companyOfficersNode as $officer) {
          $officers[] = array(
            "fullname" => $officer->field_last_name["und"][0]["safe_value"].",&nbsp;".
                          $officer->field_first_name["und"][0]["safe_value"],
            "title" => "Officer"
          );          
        }        
        
      } catch(Exception $e) {
        // Do nothing at the moment
      }
      
    }
  }
  
  
  $tqScore = $node->field_tq_score["und"][0]["value"]; // decimal
  $backgroundVerification = $node->field_background_verification["und"][0]["value"]; // bool
  $criminalRecordsCheck = $node->field_criminal_records_check["und"][0]["value"]; // decimal
  $civilRecordsCheck = $node->field_criminal_records_check["und"][0]["value"]; // decimal
  $patriotActCheck = $node->field_patriot_act_check["und"][0]["value"]; // decimal
 
?>





<div id="main-report-wrapper">
  <div id="main-report-inner">
    <div class="contain" id="report-header">
      <a href="/" id="logo" rel="home" title="Home"> <img alt="Home" src="/sites/all/themes/seven_doublemthemes/logo.png" /> </a>
      <h1>
        Enterprise Management Report</h1>
      <div id="reported-company">
        <div class="left">
          <h2><?php echo $company_name; ?></h2>
          <p><?php echo $company_description; ?></p>
          <p class="address"><?php echo $company_address; ?></p>
          <p class="phone">Phone: <?php echo $company_phone; ?></p>
          <p class="website"><a href="<?php echo $company_url; ?>" target="_blank"><?php echo $company_url; ?></a></p>
        </div>
        <div class="right">
          <label id="company-titles">Key Executives and Shareholders</label>
          <ul>
            <?php
            foreach ($officers as $officer) {
              echo '<li>'.
                      '<span class="title">' . $officer['title'] . 
                      '</span> - ' . $officer['fullname'] . 
                    '</li>';
            }
            
            ?>
          </ul>
        </div>
      </div>
    </div>
    <div id="report-body">
      
      <div class="report-group toggle-group">
        <div class="group-header no-details">
          <h3>TQ Score<sup>TM</sup></h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?php echo decimalToWord($tqScore); ?>">
              <?php echo $tqScore; ?></div>
          </div>
          <div class="no-toggle"></div>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>Background Verification</h3>
          <div class="rating"><label><?php echo $backgroundVerification?"PASSED":"FAILED"; ?></label></div>
          <div class="toggle opened" rel="report-BV">
            CLOSE</div>
          <div class="toggle closed" rel="report-BV">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-BV">
          <ul id="group-body-items">
            <?php echo getList($node, "background_verification"); ?>
          </ul>
        </div>
      </div>
      
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>
            Criminal Records Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?php echo decimalToWord($criminalRecordsCheck); ?>">
              <?php echo  $criminalRecordsCheck ?></div>
          </div>
          <div class="toggle opened" rel="report-CRC">
            CLOSE</div>
          <div class="toggle closed" rel="report-CRC">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-CRC">
          <ul id="group-body-items">
            <?php echo getList($node, "criminal_records"); ?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header">
          <h3>
            Civil Records Check</h3>
          <div class="rating">
            <label>total</label>
            <div class="stars <?php echo decimalToWord($civilRecordsCheck); ?>">
              <?php echo  $civilRecordsCheck ?></div>
          </div>
          <div class="toggle opened" rel="report-CivRC">
            CLOSE</div>
          <div class="toggle closed" rel="report-CivRC">
            MORE INFO</div>
        </div>
        <div class="group-body toggle-container" id="report-CivRC">
          <ul id="group-body-items">
            <?php echo getList($node, "civil_records"); ?>
          </ul>
        </div>
      </div>
      <div class="report-group toggle-group">
        <div class="group-header no-details">
          <h3>Patriot Act Check</h3>
          <div class="rating"><label><?php echo $patriotActCheck?"PASSED":"FAILED"; ?></label></div>
          <div class="no-toggle"></div>
        </div>
      </div>
    </div>
  </div>
</div>







<?php

function getList($node, $listName) {
  $html = "";
  if($listName == "background_verification") {
    $html = getBackgroundVerificationList($node);
  } else if($listName == "criminal_records") {
    $html = getCriminalRecordsList($node);
  } else if($listName == "civil_records") {
    $html = getCivilRecordsList($node);
  }
  return $html;
}

function getBackgroundVerificationList($node) {
  $html = getItemHTML($node, "field_name_verification").
          getItemHTML($node, "field_positive_id_auth").
          getItemHTML($node, "field_alias_search");
  return $html;
}

function getCriminalRecordsList($node) {
  $html = getItemHTML($node, "field_nat_felony_search").
          getItemHTML($node, "field_nat_misdmnr_search");
  return $html;
}

function getCivilRecordsList($node) {
  $html = getItemHTML($node, "field_judgements").
          getItemHTML($node, "field_tax_liens").
          getItemHTML($node, "field_bankruptcies").
          getItemHTML($node, "field_pending_litigations");
  return $html;
}

function getItemHTML($node, $fieldName) {
  
  $icon = getItemIcon($node, $fieldName);
  
  return '<li>'.
          '<span class="left-col" 
                 title="'.getHelpText($fieldName).'">'.
              getFieldLabel($fieldName).
          '</span>'.
          '<span class="report-icon '.$icon.'" 
                 title="'.getIconHelpText($icon).'">'.
              $icon.
          '</span>'.
          '<div class="right-col">'.
            '<p>'.getDescriptionText($node, $fieldName).'</p>'.
          '</div>'.
        '</li>';
}


function decimalToWord($decimal) {
  $word = "zero";
  
  if($decimal > 0.00 && $decimal < 1.00) {
    $word = "half";
  } else if($decimal == 1.00) {
    $word = "one";
  } else if($decimal > 1.00 && $decimal < 2.00) {
    $word = "one-half";
  } else if($decimal == 2.00) {
    $word = "two";
  } else if($decimal > 2.00 && $decimal < 3.00) {
    $word = "two-half";
  } else if($decimal == 3.00) {
    $word = "three";
  } else if($decimal > 3.00 && $decimal < 4.00) {
    $word = "three-half";
  } else if($decimal == 4.00) {
    $word = "four";
  } else if($decimal > 4.00 && $decimal < 5.00) {
    $word = "four-half";
  } else if($decimal == 5.00) {
    $word = "five";
  }
  
  return $word;
}

function getItemIcon($node, $fieldName) {

  $fieldObject = $node->$fieldName;
  $value = $fieldObject["und"][0]["value"];
  
  $fieldInfoObject = field_info_field($fieldName);
  $values = $fieldInfoObject["settings"]["allowed_values"];
  
  return strtolower($values[$value]);

}

function getHelpText($fieldName) {
  $fieldInfo = field_info_instance('node', $fieldName, 'report_card');
  return $fieldInfo["description"];
}

function getFieldLabel($fieldName) {
  $fieldInfo = field_info_instance('node', $fieldName, 'report_card');
  return $fieldInfo["label"];
}

function getDescriptionText($node, $fieldName) {
  $fieldName .= "_desc";
  $fieldObject = $node->$fieldName;
  return $fieldObject["und"][0]["value"];
}

function getIconHelpText($icon) {
  $helpText = "";
  if($icon == "pass") {
    $helpText = "Green.  This means everything for this line item checked out OK.";
  } else if($icon == "fail") {
    $helpText = "Failure.";
  } else if($icon == "note") {
    $helpText = "Informational.  This means information about this specific line item was found but likely doesn't warrant further investigation.";
  } else if($icon == "warn") {
    $helpText = "Warning.";
  }
}

?>
