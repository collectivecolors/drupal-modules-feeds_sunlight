<?php

/**
 * @file
 * Sunlight API Legislator Parser plugin.
 */

/**
 * Feeds parser plugin that parses Sunlight legislator information.
 */
class FeedsSunlightLegislatorParser extends FeedsParser {
	
  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {  	
  	$legislators = array();
  	
  	foreach ($fetcher_result->getRaw() as $data) {
  		
    	$legislator = $data->legislator;
    	$item       = array();
    	
    	// Profile information
    	$item['label'] = t('@t @fn @mn @ln @ns ( @p @s )', array(
    		'@t'  => $legislator->title,
    		'@fn' => $legislator->firstname, 
    		'@mn' => $legislator->middlename,
    		'@ln' => $legislator->lastname,
    		'@ns' => $legislator->name_suffix,
    		'@s'  => $legislator->state,
    		'@p'  => $legislator->party,
    	));
    	
    	$item['firstname']   = $legislator->firstname;
    	$item['middlename']  = $legislator->middlename;
    	$item['lastname']    = $legislator->lastname;
    	$item['name_suffix'] = $legislator->name_suffix;
    	$item['nickname']    = $legislator->nickname;
    	$item['gender']      = $legislator->gender;
    	$item['birthdate']   = $legislator->birthdate;
    	
    	/*$base_image_path = file_default_scheme() . ':/legislators';
    	
    	// 200x250 images placed into the files/legislators directory.
    	$large_image_path = $base_image_path . '/200x250/';
    	if (is_dir($large_image_path)) {
    		$item['200x250'] = $large_image_path	. $legislator->bioguide_id . '.jpg';
    	}*/
    	
    	// Office information
    	$item['title']           = $legislator->title;
    	$item['in_office']       = $legislator->in_office;
    	$item['chamber']         = $legislator->chamber;
    	$item['senate_class']    = $legislator->senate_class;    	
    	$item['district']        = $legislator->district;
    	$item['state']           = $legislator->state;
    	$item['party']           = $legislator->party;
    	$item['congress_office'] = $legislator->congress_office;
    	$item['website']         = $legislator->website;
    	
    	// Communication channels
    	$item['phone']             = $legislator->phone;
    	$item['fax']               = $legislator->fax;
    	$item['email']             = $legislator->email;
    	$item['webform']           = $legislator->webform;    	
    	$item['official_rss']      = $legislator->official_rss;
    	$item['congresspedia_url'] = $legislator->congresspedia_url;
    	$item['youtube_url']       = $legislator->youtube_url;
    	$item['twitter_id']        = $legislator->twitter_id;
    	$item['facebook_id']       = $legislator->facebook_id;
    	
    	// Misc ids
    	$item['fec_id']       = $legislator->fec_id;
    	$item['crp_id']       = $legislator->crp_id;
    	$item['govtrack_id']  = $legislator->govtrack_id;
    	$item['votesmart_id'] = $legislator->votesmart_id;
    	$item['eventful_id']  = $legislator->eventful_id;
    	$item['bioguide_id']  = $legislator->bioguide_id;   	
    	    	
    	$legislators[] = $item;    	
    }
    
    return new FeedsParserResult($legislators);
  }

  /**
   * Return mapping sources.
   */
  public function getMappingSources() {
    return array(
    	// Profile information
    	'label' => array(
        'name' => t('Label'),
        'description' => t('Label for use in a title or other display built out of firstname, lastname, etc...'),
    	),
      'firstname' => array(
        'name' => t('First name'),
        'description' => t('First name of the legislator.'),
      ),
      'middlename' => array(
        'name' => t('Middle name'),
        'description' => t('Middle name of the legislator.'),
      ),
    	'lastname' => array(
        'name' => t('Last name'),
        'description' => t('First name of the legislator.'),
    	),
    	'name_suffix' => array(
        'name' => t('Name suffix'),
        'description' => t('Optional name suffix of the legislator.'),
    	),
      'nickname' => array(
        'name' => t('Nickname'),
        'description' => t('Nickname of the legislator.'),
    	),
    	'gender' => array(
        'name' => t('Gender'),
        'description' => t('Gender of the legislator.'),
    	),
    	'birthdate' => array(
        'name' => t('Birthdate'),
        'description' => t('Birthdate of the legislator.'),
    	),
    	'200x250' => array(
        'name' => t('200x250 official image'),
        'description' => t('200x250 official ima of the legislator.'),
    	),
    	
    	// Office information
      'title' => array(
      	'name' => t('Title'),
        'description' => t('Title of the legislator.'),
    	),
      'in_office' => array(
      	'name' => t('Currently in office?'),
        'description' => t('Whether the legislator is still in office.'),
    	),
      'chamber' => array(
        'name' => t('Chamber'),
        'description' => t('Chamber of the legislator.'),
    	),
      'senate_class' => array(
        'name' => t('Senate class'),
        'description' => t('Senate class of the legislator.'),
    	),
      'district' => array(
        'name' => t('District'),
        'description' => t('District of the legislator.'),
    	),
      'state' => array(
        'name' => t('State'),
        'description' => t('State of the legislator.'),
    	),
      'party' => array(
        'name' => t('Party'),
        'description' => t('Political party of the legislator.'),
    	),
    	'congress_office' => array(
        'name' => t('Congressional office'),
        'description' => t('Congrssional office of the legislator.'),
    	),
    	'website' => array(
        'name' => t('Website'),
        'description' => t('Website of the legislator.'),
    	),
    
    	// Communication channels
    	'phone' => array(
    		'name' => t('Phone number'),
        'description' => t('Phone number of the legislator.'),
      ),
      'fax' => array(
       	'name' => t('Fax number'),
        'description' => t('Fax number of the legislator.'),
      ),
      'email' => array(
    		'name' => t('Email'),
        'description' => t('Email address of the legislator.'),
      ),
      'webform' => array(
      	'name' => t('Webform'),
    		'description' => t('Webform url of the legislator.'),
      ),
      'official_rss' => array(
    		'name' => t('Official RSS'),
    		'description' => t('Official RSS feed of the legislator.'),
      ),
    	'congresspedia_url' => array(
      	'name' => t('Congresspedia url'),
        'description' => t('Congresspedia url of the legislator.'),
    	),
      'youtube_url' => array(
      	'name' => t('Youtube url'),
    		'description' => t('Youtube url of the legislator.'),
    	),
    	'twitter_id' => array(
      	'name' => t('Twitter name'),
        'description' => t('Twitter name of the legislator.'),
      ),
    	'facebook_id' => array(
      	'name' => t('Facebook name'),
        'description' => t('Facebook name of the legislator.'),
      ),
      
    	// Misc ids
      'fec_id' => array(
      	'name' => t('FEC id'),
        'description' => t('FEC id of the legislator.'),
    	),
      'crp_id' => array(
      	'name' => t('CRP id'),
        'description' => t('CRP id of the legislator.'),
    	),
      'govtrack_id' => array(
      	'name' => t('GovTrack id'),
        'description' => t('GovTrack id of the legislator.'),
    	),
      'votesmart_id' => array(
      	'name' => t('VoteSmart id'),
        'description' => t('VoteSmart id of the legislator.'),
    	),
      'eventful_id' => array(
      	'name' => t('Eventful id'),
        'description' => t('Eventful id of the legislator.'),
    	),
      'bioguide_id' => array(
      	'name' => t('BioGuide id'),
        'description' => t('BioGuide id of the legislator.'),
    	),
    ) + parent::getMappingSources();
  }
}
