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
            "fullname" => $officer->field_first_name["und"][0]["safe_value"]."&nbsp;".
                          $officer->field_last_name["und"][0]["safe_value"],
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
  $civilRecordsCheck = $node->field_civil_records_check["und"][0]["value"]; // decimal

  // Retrieve the Patriot Act value
  $patriotActObj = field_info_field("field_patriot_act_check");
  $patriotActObjValues = $patriotActObj["settings"]["allowed_values"];
  $patriotActCheck = $patriotActObjValues[$node->field_patriot_act_check["und"][0]["value"]];
  
  $softwareVersion = $node->field_software_version["und"][0]["value"];
?>





<div id="main-report-wrapper">
  <div id="main-report-inner">
    <div class="contain" id="report-header">
      <a href="/" id="logo" rel="home" title="Home"> <img alt="Home" src="/sites/all/themes/earlyiq/logo.png" /> </a>
      <h1>Kiva Zip Applicant Report</h1>
      <div id="reported-company">
      
        <div class="left">
					<h2><?php echo $company_name; ?></h2>
					<?php
            foreach ($officers as $officer) {
              echo   '<p>Applicant:&nbsp;'.$officer['fullname'].'</p>';
            }
            ?>
				</div>
				<div class="right">
					<ul>
					</ul>
				</div>
				
      <!--
      
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
      
      //-->
    </div>
    <div id="report-body">
      <div id="softwareVersion" style="display:none;"><?php echo $softwareVersion; ?></div>
      <div class="report-group toggle-group">
        <div class="group-header no-details">
          <h3 title="The TQScore is the result of our proprietary algorithms which together model the historical and predicted future transparency of the business operation.  The TQScore is not a summary or average of the other scores shown on the report card.">TQ Score<sup>TM</sup></h3>
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
          <h3 title="The Background Verification score is a summary score of the line items within the section.  In the case of Kiva Zip, borrowers will either receive a 5 star rating (successfully passed the Identity Validation) or an Incomplete (we were unable to validate the borrowers identity and no further action was taken).">Background Verification</h3>
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
          <h3 title="The Criminal Record Check score is a summary score of the line items within the section.  In the case of Kiva Zip, a national database search was conducted based on the verified identity of the applicant.  Individual county of residence record searches were not performed.  If the applicant's identity could not be verified, this score and section will be marked incomplete.">Criminal Records Check</h3>
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
          <h3 title="The Civil Record Check score is a summary score of the line items within the section.  In the case of Kiva Zip, a national database search was conducted based on the verified identity of the applicant.  Individual county of residence record searches were not performed.  If the applicant's identity could not be verified, this score and section will be marked incomplete.">Civil Records Check</h3>
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
          <div class="rating"><label><?php echo strtoupper($patriotActCheck); ?></label></div>
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
  
  $iconHelpText = getIconHelpText($icon, $fieldName);
  $iconHoverText = getIconHoverText($icon);
  
  $descriptionText = getDescriptionText($node, $fieldName);
  
  $descriptionElementHTML = "";
  
  if(!empty($descriptionText)) {
  
    $descriptionElementHTML = 
    '<div class="report-details-toggle">'.
    	'<a rel="div_'.$fieldName.'" class="show-detail" style="display: block;">Details</a>'.
    	'<a rel="div_'.$fieldName.'" class="hide-detail" style="display: none;">Close</a>'.
  	  '<div id="div_'.$fieldName.'" class="details-toggle-container">'.
    		'<pre><p>'.$descriptionText.'</p></pre>'.
  	  '</div>';
    '</div>';
  }
  
  return '<li>'.
          '<span class="left-col" 
                 title="'.getHelpText($fieldName).'">'.
              getFieldLabel($fieldName).
          '</span>'.
          '<span class="report-icon '.$icon.'" 
                 title="'.$iconHoverText.'">'.
              $icon.
          '</span>'.
          '<div class="right-col">'.
            '<p>'.$iconHelpText.'</p>'.
            $descriptionElementHTML.
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
  $fieldValue = null;
  if(!empty($fieldObject)) {
    $fieldValue = $fieldObject["und"][0]["value"];
  }
  return $fieldValue;
}



function getIconHoverText($icon) {
  $hoverText = "";
  
  if($icon == "pass") {
    $hoverText = "Green.  This means everything for this line item checked out OK.";
  } else if($icon == "fail") {
    $hoverText = "Red.  This means information about this specific line item was found that is view negatively compared to the average.  Further investigation is suggested.";
  } else if($icon == "note") {
    $hoverText = "Informational.  This means information about this specific line item was found but likely doesn't warrant further investigation.";
  } else if($icon == "warn") {
    $hoverText = "Yellow.  This means information about this specific line item was found that may warrant further investigation.";
  }
  return $hoverText;
}

function getIconHelpText($icon, $fieldName) {

  $helpText = "";
  if($icon == "pass") {
    
    switch($fieldName) {
      case "field_name_verification": 
        $helpText = "Borrower personally identifiable information shows no major inconsistencies.";
        break;
      case "field_positive_id_auth":
        $helpText = "Borrower passed identity validation.  Stolen or fictitious identity unlikely.";   
        break;
      case "field_alias_search":
        $helpText = "";
        break;    
      case "field_nat_felony_search":
        $helpText = "No felonies convictions found";
        break;    
      case "field_nat_misdmnr_search":
        $helpText = "No misdemeanor convictions found";
        break;    
      case "field_judgements":
        $helpText = "No judgment records against borrower found";
        break;    
      case "field_tax_liens":
        $helpText = "No tax lien records for borrower found";
        break;    
      case "field_bankruptcies":
        $helpText = "No personal bankruptcy records were found.";
        break;    
      case "field_pending_litigations":
        $helpText = "No pending civil litigation records against borrower were found";
        break;    
    }
  } else if($icon == "fail") {
  
    switch($fieldName) {
      case "field_name_verification": 
        $helpText = "Borrower personally identifiable information is inconsistent.  No further analysis conducted.";
        break;
      case "field_positive_id_auth":
        $helpText = "Borrower failed identity validation.   No further analysis conducted.";   
        break;
      case "field_alias_search":
        $helpText = "";
        break;    
      case "field_nat_felony_search":
        $helpText = "Significant felony conviction history found.";
        break;    
      case "field_nat_misdmnr_search":
        $helpText = "Significant misdemeanor conviction history found.";
        break;    
      case "field_judgements":
        $helpText = "Significant civil judgment history against borrower found.";
        break;    
      case "field_tax_liens":
        $helpText = "";
        break;    
      case "field_bankruptcies":
        $helpText = "";
        break;    
      case "field_pending_litigations":
        $helpText = "";
        break;    
    }

    
  } else if($icon == "note") {
  
    switch($fieldName) {
      case "field_name_verification": 
        $helpText = "";
        break;
      case "field_positive_id_auth":
        $helpText = "";   
        break;
      case "field_alias_search":
        $helpText = "Shown for information only.";
        break;    
      case "field_nat_felony_search":
        $helpText = "";
        break;    
      case "field_nat_misdmnr_search":
        $helpText = "1 self-disclosed misdemeanor conviction was confirmed for a non-white-collar crime.";
        break;    
      case "field_judgements":
        $helpText = "No unsatisfied judgments against borrower found for non-fraud-related cases.";
        break;    
      case "field_tax_liens":
        $helpText = "Tax lien(s) for borrower found";
        break;    
      case "field_bankruptcies":
        $helpText = "A personal bankruptcy was found.";
        break;    
      case "field_pending_litigations":
        $helpText = "Pending litigation againsts borrower was found for a non-fraud-related case.";
        break;    
    }

    
  } else if($icon == "warn") {
  
    switch($fieldName) {
      case "field_name_verification": 
        $helpText = "";
        break;
      case "field_positive_id_auth":
        $helpText = "";   
        break;
      case "field_alias_search":
        $helpText = "";
        break;    
      case "field_nat_felony_search":
        $helpText = "1 self-disclosed felony conviction was confirmed for a non-white-collar crime.";
        break;    
      case "field_nat_misdmnr_search":
        $helpText = "Marginal misdemeanor conviction history found";
        break;    
      case "field_judgements":
        $helpText = "Marginal civil judgment history against borrower found.";
        break;    
      case "field_tax_liens":
        $helpText = "";
        break;    
      case "field_bankruptcies":
        $helpText = "";
        break;    
      case "field_pending_litigations":
        $helpText = "Pending litigation was found against borrower for a fraud related case";
        break;    
    }
  }
  
  return $helpText;
}

?>
